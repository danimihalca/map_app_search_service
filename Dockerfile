ARG SRC_PATH=/workspace/map_app_search_service
ARG BUILD_DBG_DIR=buildDbg
ARG BUILD_REL_DIR=buildRel
ARG BUILD_DBG_PATH=${SRC_PATH}/${BUILD_DBG_DIR}
ARG BUILD_REL_PATH=${SRC_PATH}/${BUILD_REL_DIR}

FROM emscripten/emsdk:3.1.57 as base_devel_env
ARG SRC_PATH
COPY . ${SRC_PATH}
WORKDIR ${SRC_PATH}

FROM base_devel_env as debug_config
ARG SRC_PATH
ARG BUILD_DBG_PATH
RUN mkdir -p ${BUILD_DBG_PATH}
WORKDIR ${BUILD_DBG_PATH}
RUN emcmake cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=out ${SRC_PATH}

FROM debug_config as build_debug
RUN make install

FROM base_devel_env as release_config
ARG SRC_PATH
ARG BUILD_REL_PATH
RUN mkdir -p ${BUILD_REL_PATH}
WORKDIR ${BUILD_REL_PATH}
RUN emcmake cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=out ${SRC_PATH}

FROM release_config as build_release
RUN make install

FROM scratch as get_release_build
ARG BUILD_REL_PATH
COPY --from=build_release ${BUILD_REL_PATH}/out .
