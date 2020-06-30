bash root/restart_services.sh
cd /etc/nginx/ && mv nginx.conf nginx.conf.ORIG && mv /etc/php/7.3/fpm/php-fpm.conf /etc/php/7.3/fpm/php-fpm.conf.ORIG && mv /etc/php/7.3/fpm/php.ini /etc/php/7.3/fpm/php.ini.ORIG
mkdir -p /home/ft_server/logs /usr/share/nginx/cache/fcgi /var/run/php-fpm && rm /etc/php/7.3/fpm/pool.d/www.conf
cp ./root/nginx.conf ./etc/nginx && cp ./root/php-fpm.conf ./etc/php/7.3/fpm/ && cp ./root/www.conf ./etc/php/7.3/fpm/pool.d/www.conf && cp ./root/php.ini ./etc/php/7.3/fpm/php.ini
bash root/restart_services.sh
bash ./root/sql_init.sh
bash root/restart_services.sh
adduser --disabled-password --gecos "" ft_server
mkdir -p /home/ft_server/logs && cp ./root/ft_server.conf /etc/nginx/conf.d/ && rm /etc/nginx/sites-enabled/default
cp ./root/ft_server_php.conf etc/php/7.3/fpm/pool.d
touch /home/ft_server/logs/phpfpm_error.log
bash ~/create_database.sh
tail -f /dev/null
