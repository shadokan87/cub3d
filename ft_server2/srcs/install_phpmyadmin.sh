echo "wget https://files.phpmyadmin.net/phpMyAdmin/4.9.5/phpMyAdmin-4.9.5-all-languages.tar.gz" | su - ftserver
echo "tar zxf phpMyAdmin-4.9.5-all-languages.tar.gz" | su - ftserver
echo "mv phpMyAdmin-4.9.5-all-languages phpmyadmin" | su - ftserver
echo "rm phpMyAdmin-4.9.5-all-languages.tar.gz" | su - ftserver
echo "mv phpmyadmin public_html" | su - ftserver
cp ~/config.inc.php /home/ftserver/public_html/phpmyadmin
