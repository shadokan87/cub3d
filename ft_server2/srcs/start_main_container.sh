cp /etc/hosts /etc/hosts2
sed -i '1 s/localhost/www.ftserver.com/' /etc/hosts2
echo "127.0.0.1		https://ftserver.com" >> /etc/hosts2
echo "ftserver.com		https://ftserver.com" >> /etc/hosts2
cat /etc/hosts2 > /etc/hosts
service nginx start
service php7.3-fpm start
service mysql stop
service mysql start
tail -f /dev/null
