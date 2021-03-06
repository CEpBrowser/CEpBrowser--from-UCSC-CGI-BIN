#!/bin/tcsh
cd $WEEKLYBLD
if ( "$HOST" != "hgwdev" ) then
 echo "error: doTrackCheckRobot.csh must be executed from hgwdev!"
 exit 1
endif

# run on hgwdev, but using hgwbeta HG.CONF settings for the database
set log = TrackCheck-v${BRANCHNN}.log
set HGDB_CONF = $HOME/.hg.conf.beta
cd $JAVABUILD/kent/java/classes/edu/ucsc/genome/qa/cgiCheck
nohup TrackCheck $JAVABUILD/kent/java/src/edu/ucsc/genome/qa/cgiCheck/full.props >& $WEEKLYBLD/logs/$log 
# tail -f $WEELYBLD/logs/$log
# egrep -i "not|warn|err" $WEEKLYBLD/logs/$log

echo "TrackCheck robot done. Check to see if any errors in $WEEKLYBLD/logs/$log."

exit 0

