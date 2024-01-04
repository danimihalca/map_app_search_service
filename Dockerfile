ARG BASE_ENV=map-app-search-service-rel-env
ARG SRC_PATH=/workspace/map_app_search_service
ARG BUILD_DBG_DIR=buildDbg
ARG BUILD_REL_DIR=buildRel
ARG BUILD_DBG_PATH=${SRC_PATH}/${BUILD_DBG_DIR}
ARG BUILD_REL_PATH=${SRC_PATH}/${BUILD_REL_DIR}

FROM ${BASE_ENV} as base_devel_env
ARG SRC_PATH
COPY . ${SRC_PATH}
WORKDIR ${SRC_PATH}

FROM base_devel_env as debug_config
ARG SRC_PATH
ARG BUILD_DBG_PATH
RUN mkdir -p ${BUILD_DBG_PATH}
WORKDIR ${BUILD_DBG_PATH}
RUN cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=out -DCONAN_DEPS_PATH=/workspace/search-service-dependencies-rel ${SRC_PATH}

FROM debug_config as build_debug
RUN make install

FROM build_debug as run_unit_tests
RUN cd out/bin && \
    ./map_app_search_service_unit_tests --gtest_output="xml:report.xml"

FROM scratch as get_unit_tests_report
ARG BUILD_DBG_PATH
COPY --from=run_unit_tests ${BUILD_DBG_PATH}/out/bin/report.xml .

FROM build_debug as run_coverage
RUN make coverage

FROM scratch as get_coverage
ARG BUILD_DBG_PATH
COPY --from=run_coverage ${BUILD_DBG_PATH}/tests/unit_tests/coverage .

FROM base_devel_env as release_config
ARG SRC_PATH
ARG BUILD_REL_PATH
RUN mkdir -p ${BUILD_REL_PATH}
WORKDIR ${BUILD_REL_PATH}
RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=out -DCONAN_DEPS_PATH=/workspace/search-service-dependencies-rel ${SRC_PATH}

FROM release_config as build_release
RUN make install

FROM scratch as get_release_build
ARG BUILD_REL_PATH
COPY --from=build_release ${BUILD_REL_PATH}/out .

FROM debian as runner
ENV MAPBOX_TOKEN ""
ARG BUILD_REL_PATH

RUN apt update && apt install -y ca-certificates
RUN mkdir /workspace
WORKDIR /workspace
COPY --from=build_release ${BUILD_REL_PATH}/out .

EXPOSE 12345

RUN chmod 755 /workspace/bin/map_app_search_service_bin
COPY entrypoint.sh /workspace/entrypoint.sh
RUN chmod +x /workspace/entrypoint.sh

ENTRYPOINT /workspace/entrypoint.sh

# docker build --build-arg="APP=./build/out" -t map-app-search-service-run .
# docker run -dit -p 12345:12345 -e MAPBOX_TOKEN=<TOKEN> map-app-search-service-run