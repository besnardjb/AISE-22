FROM ubuntu

RUN apt-get update && apt-get install nginx -y && apt-get clean

EXPOSE 80/tcp

CMD ["nginx", "-g", "daemon off;"]
