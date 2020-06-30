mkdir /var/run/php-fpm
cp ~/php-fpm.conf /etc/php/7.3/fpm/
rm /etc/php/7.3/fpm/pool.d/www.conf
cp ~/www.conf /etc/php/7.3/fpm/pool.d/
cp ~/php.ini /etc/php/7.3/fpm/
cp ~/ftserver_php.conf /etc/php/7.3/fpm/pool.d/ftserver.conf
touch /home/ftserver/logs/phpfpm_error.log
