service nginx start
service php7.3-fpm start
service mysql stop
service mysql start
cp /etc/hosts /etc/hosts2
sed -i '1 s/localhost/www.ftserver.com/' /etc/hosts2
cat /etc/hosts2 > /etc/hosts
tail -f /dev/null
