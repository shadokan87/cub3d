cp ~/nginx.conf /etc/nginx
cp ~/ftserver.conf /etc/nginx/conf.d
mkdir -p /usr/share/nginx/cache/fcgi
adduser --disabled-password --gecos "" ftserver
mkdir -p /home/ftserver/logs
rm /etc/nginx/sites-enabled/default
bash ~/restart_nginx.sh
