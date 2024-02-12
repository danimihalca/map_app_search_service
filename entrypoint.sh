#!/bin/bash

[ -f /run/secrets/mapbox_token ] && MAPBOX_TOKEN_VALUE=`cat /run/secrets/mapbox_token` || MAPBOX_TOKEN_VALUE=${MAPBOX_TOKEN}

echo "Starting service app..."
exec /workspace/map_app_search_service $MAPBOX_TOKEN_VALUE
echo "Stopping service app..."
