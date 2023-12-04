#include <gtest/gtest.h>

#include "serviceImpl/MapBoxPlacesPathBuilder.h"

class MapBoxPlacesPathBuilderTest : public testing::Test
{
};

TEST_F(MapBoxPlacesPathBuilderTest, normal_build)
{
    auto pathBuilder = serviceImpl::MapBoxPlacesPathBuilder("<ACCESS_TOKEN>");

    pathBuilder.withBasePath("http://basepath.com/");
    pathBuilder.withQuery("kfc");

    auto output = pathBuilder.build();
    EXPECT_EQ(output, "http://basepath.com/kfc.json?access_token=<ACCESS_TOKEN>");
}

TEST_F(MapBoxPlacesPathBuilderTest, build_with_extra_parameters)
{
    auto pathBuilder = serviceImpl::MapBoxPlacesPathBuilder("<ACCESS_TOKEN>");

    pathBuilder.withBasePath("http://basepath.com/");
    pathBuilder.withQuery("kfc");
    pathBuilder.withParameter("limit", "5");
    pathBuilder.withParameter("location", "UK");

    auto output = pathBuilder.build();
    EXPECT_EQ(output, "http://basepath.com/kfc.json?limit=5&location=UK&access_token=<ACCESS_TOKEN>");
}

TEST_F(MapBoxPlacesPathBuilderTest, multiple_builds_with_clear)
{
    auto pathBuilder = serviceImpl::MapBoxPlacesPathBuilder("<ACCESS_TOKEN>");

    pathBuilder.withBasePath("http://basepath.com/");
    pathBuilder.withQuery("kfc");
    pathBuilder.withParameter("limit", "5");
    pathBuilder.withParameter("location", "UK");

    auto output = pathBuilder.build();
    EXPECT_EQ(output, "http://basepath.com/kfc.json?limit=5&location=UK&access_token=<ACCESS_TOKEN>");

    pathBuilder.reset();

    pathBuilder.withBasePath("http://basepath2.com/");
    pathBuilder.withQuery("kfc2");
    pathBuilder.withParameter("limit2", "11");
    pathBuilder.withParameter("location2", "US");

    output = pathBuilder.build();
    EXPECT_EQ(output, "http://basepath2.com/kfc2.json?limit2=11&location2=US&access_token=<ACCESS_TOKEN>");
}