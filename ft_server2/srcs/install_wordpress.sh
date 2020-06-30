echo "wget https://wordpress.org/latest.tar.gz" | su - ftserver
echo "tar zxf latest.tar.gz" | su - ftserver
echo "rm latest.tar.gz" | su - ftserver
echo "mv wordpress public_html" | su - ftserver
