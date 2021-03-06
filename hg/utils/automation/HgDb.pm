#
# HgDb: Class interface to the mysql databases
# Get's relevant mysql connect data from the .hg.conf file
#
# DO NOT EDIT the /cluster/bin/scripts copy of this file --
# edit ~/kent/src/hg/utils/automation/HgDb.pm instead.

# $Id: HgDb.pm,v 1.9 2010/05/25 00:52:56 krish Exp $

package HgDb;

use warnings;
use strict;

use Carp;
use DBI;

use vars qw(@ISA @EXPORT_OK);
use Exporter;

@ISA = qw(Exporter);

sub new
{
# $args{DB} is required
# $args{PROFILE}: let's you select db profile (optional: defaults to "db").
# $args{USER}, $args{PASSWORD} and $args{HOST} are optional (and override .hg.conf values).
    my ($class, %args) = (@_);
    my $ref = {};
    if(!defined($args{DB})) {
        die "Missing \$args{DB}";
    }
    my $dsn = "DBI:mysql:$args{DB}";
    my $confFile = "$ENV{HOME}/.hg.conf";
    if(! -e $confFile) {
        die "Cannot locate conf file: '$confFile'";
    }
    my $profile = $args{PROFILE} || "db";
    open(CONF, $confFile);
    for (<CONF>) {
        next if /^#/;
        if(/^include/) {
            # XXXX TODO: support "include ../cgi-bin/hg.conf"
            die "include ... syntax not currently supported";
        }
        for my $name (qw(host user password)) {
            if(/^$profile\.$name\s*=\s*(.+)/) {
                $ref->{uc($name)} = $1;
            }
        }
    }
    close(CONF);
    for (keys %args) {
        # %args override values in conf file.
        $ref->{$_} = $args{$_};
    }
    if($ref->{HOST}) {
        $dsn .= ";host=$ref->{HOST}";
    }
    $ref->{DBH} = DBI->connect($dsn, $ref->{USER}, $ref->{PASSWORD}) or die "Couldn't connect to db: $ref->{DB}";
    bless $ref, 'HgDb';
    return $ref;
}

sub disconnect
{
    my ($db) = (@_);
    $db->{DBH}->disconnect();
    $db->{DBH} = undef;
}

sub DESTROY
{
    my ($db) = (@_);
    if($db->{DBH}) {
        $db->disconnect();
    }
}

sub execute
{
# Execute given query with @params substituted for placeholders in the query
# Returns $sth
    my ($db, $query, @params) = (@_);
    my $sth = $db->{DBH}->prepare($query) or die "prepare for query '$query' failed; error: " . $db->{DBH}->errstr;
    if(!$sth->execute(@params)) {
        die "execute for query '$query' failed; error: " . $db->{DBH}->errstr;
    }
    return $sth;
}

sub quickQuery
{
# Execute given query with @params substituted for placeholders in the query.
# Returns first field in first row.
# Return undef if query comes up empty.
    my ($db, $query, @params) = (@_);
    my $sth = $db->{DBH}->prepare($query) or die "prepare for query '$query' failed; error: " . $db->{DBH}->errstr;
    if(!$sth->execute(@params)) {
        die "execute for query '$query' failed; error: " . $db->{DBH}->errstr;
    }
    my @row = $sth->fetchrow_array();
    return @row ? $row[0] : undef;
}

sub update
{
    my ($db, $query, @params) = (@_);
    my $count = $db->{DBH}->do($query, {}, @params);
    return $count;
}

sub insert
{
    my ($db, $table, $fields, $values) = (@_);
    my $placeholders = join(",", (("?") x @{$fields}));
    my $query = "insert into $table (" . join(",", @{$fields}) . ") VALUE ($placeholders)";
    my $sth = $db->{DBH}->prepare($query) or die "prepare for query '$query' failed; error: " . $db->{DBH}->errstr;
    if(!$sth->execute(@{$values})) {
        die "execute for query '$query' failed; error: " . $db->{DBH}->errstr;
    }
}


sub tableExist
{
    my ($db, $tableName) = @_;
    my $retval = 0;
    my $sth = $db->execute("show tables like ?", $tableName);
    my @row = $sth->fetchrow_array();
    if(@row && $row[0]) {
        $retval = 1 ;
    }
    return $retval;
}

sub dropTable
{
    my ($db, $tableName) = @_;
    $db->execute("drop table $tableName") || die "Couldn't drop table '$tableName'";
}

sub dropTableIfExist
{
    my ($db, $tableName) = @_;
    if(tableExist($db, $tableName)) {
        dropTable($db, $tableName);
    }
}

sub getChromInfo
{
# populate a chromInfo hash reference
    my ($db, $chromInfo) = @_;
    my $sth = $db->execute("select chrom from chromInfo");
    while(my @row = $sth->fetchrow_array()) {
        $chromInfo->{$row[0]}++;
    }
}

sub getChromSizes
{
# populate a chromInfo hash reference ({chr1 => 666, etc.}).
    my ($db, $chromInfo) = @_;
    my $sth = $db->execute("select chrom, size from chromInfo");
    while(my @row = $sth->fetchrow_array()) {
        $chromInfo->{$row[0]} = $row[1];
    }
}

sub quote
{
# Returns a quoted and escaped version of $string
    my ($db, $string) = (@_);
    return $db->{DBH}->quote($string) or die "escaping '$string' failed; error: " . $db->{DBH}->errstr;
}

1;
