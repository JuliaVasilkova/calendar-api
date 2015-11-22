В данной приложении используется Fastcgi Daemon — Yandex's opensource framework for design highload FastCGI applications on C++

Для его корректной установки и настройки необходимо проделать следующие шаги

Установка всех необходимых для сборки пакетов и клонирование репозитория  Fastcgi Damon

sudo apt-get install -y build-essential git debhelper automake1.9 autotools-dev libboost-dev libboost-thread-dev libfcgi-dev libxml2-dev libboost-regex-dev libtool libssl-dev autoconf-archive

git clone https://github.com/lmovsesjan/Fastcgi-Daemon.git

Теперь соберем проект:

dpkg-buildpackage -rfakeroot
cd ../
sudo dpkg -i ./libfastcgi-daemon2-dev_2.10-26_amd64.deb \
./libfastcgi-daemon2_2.10-26_amd64.deb ./fastcgi-daemon2-init_2.10-26_amd64.deb \
./fastcgi-daemon2_2.10-26_amd64.deb  ./libfastcgi2-syslog_2.10-26_amd64.deb

Если в процессе не произошло ошибок и программа установилась правильно, стоит убрать лишний файлы

rm -rf Fastcgi-Daemon *.deb fastcgi-daemon2*
apt-get autoremove --purge -y debhelper automake1.9 pkg-config autotools-dev autoconf-archive

В данной работе используется сервер nginx .  Установим его

sudo apt-get install nginx

В этом файле 
/etc/nginx/sites-available/default
необходимо прописать следуюшие настройки сервера nginx

server {
  listen 80;

  location / {
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $fastcgi_script_name;
    fastcgi_pass unix:/tmp/fastcgi_daemon.sock;
}
}

