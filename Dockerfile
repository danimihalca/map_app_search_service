FROM debian
ARG APP
ENV MAPBOX_TOKEN ""

RUN mkdir /workspace
WORKDIR /workspace
COPY $APP .

# EXPOSE 12345

ENTRYPOINT  ["/workspace/bin/map_app_search_service_bin", "$MAPBOX_TOKEN"]

# docker build --build-arg="APP=./build/out" -t map-app-search-service-run .
# docker run -dit -p 12345:12345 -e MAPBOX_TOKEN=<TOKEN> map-app-search-service-run