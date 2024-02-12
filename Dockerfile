ARG BASE_ENV=map-app-search-service-rel-env
ARG SRC_PATH=/workspace/map_app_search_service
ARG BUILD_REL_DIR=out
ARG BUILD_REL_PATH=${SRC_PATH}/${BUILD_REL_DIR}

FROM mcr.microsoft.com/dotnet/sdk:8.0 as base_devel_env
ARG SRC_PATH
COPY . ${SRC_PATH}
WORKDIR ${SRC_PATH}

FROM base_devel_env as build_release
ARG BUILD_REL_DIR
RUN dotnet publish -c Release -o ${BUILD_REL_DIR}

FROM scratch as get_release_build
ARG BUILD_REL_PATH
COPY --from=build_release ${BUILD_REL_PATH} .

FROM mcr.microsoft.com/dotnet/aspnet:8.0 as runner
ENV MAPBOX_TOKEN ""
ARG BUILD_REL_PATH

RUN mkdir /workspace
WORKDIR /workspace
COPY --from=build_release ${BUILD_REL_PATH} .

EXPOSE 12345

RUN chmod 755 /workspace/map_app_search_service
COPY entrypoint.sh /workspace/entrypoint.sh
RUN chmod +x /workspace/entrypoint.sh

ENTRYPOINT ["/workspace/entrypoint.sh"]

# docker build --build-arg="APP=./build/out" -t map-app-search-service-run .
# docker run -dit -p 12345:12345 -e MAPBOX_TOKEN=<TOKEN> map-app-search-service-run