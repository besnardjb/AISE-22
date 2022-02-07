FROM php:7.4.15-apache
RUN apt-get update && apt-get install -y redis-tools && apt-get clean

COPY ./script.sh /

CMD ["/bin/sh", "/script.sh"]
