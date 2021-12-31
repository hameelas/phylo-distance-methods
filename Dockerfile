FROM ubuntu

RUN echo "version 1.0"

RUN apt-get update
RUN apt-get -y install git python3 python3-dev python3-pip g++ make automake autotools-dev dos2unix
RUN echo 'alias python="python3"' >> ~/.bashrc

WORKDIR /data
COPY requirements.txt  requirements.txt
RUN pip install -r requirements.txt

WORKDIR /data/third-party/tps
COPY third-party/tps/ .
RUN ./install-tps.sh

WORKDIR /data/third-party/FastME-master
COPY third-party/FastME-master/ .
RUN autoreconf -f -i
RUN ./configure
RUN make
RUN make install

WORKDIR /data/third-party/clearcut
COPY third-party/clearcut/ .
RUN make

WORKDIR /data/third-party/quicktree
COPY third-party/quicktree/ .
RUN make

WORKDIR /data/third-party/rapidnj
COPY third-party/rapidnj/ .
RUN make

WORKDIR /data

COPY checker/ checker/
COPY erin_resources/ erin_resources/
COPY gen/ gen/
# COPY results .
COPY scripts/ scripts/
COPY solution/ solution/
COPY validator/ validator/
COPY *.json .

CMD [ "bash" ]
