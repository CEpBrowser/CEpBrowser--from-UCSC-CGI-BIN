for db in mm9 hg19
do
	hgsql ${db} -e "SELECT tableName FROM trackDb WHERE grp = 'encode';" > encode.txt

	cat encode.txt | \
	while read TABLENAME; do
		hgsql ${db} -e "DROP TABLE IF EXISTS \`${TABLENAME}\`;"
	done;
	hgsql ${db} -e "DELETE FROM trackDb WHERE grp = 'encode';"
done


