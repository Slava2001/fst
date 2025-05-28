#include <gtest/gtest.h>

#include "answers.h"

TEST(Answers, Serialize) {
    Answers a = {{{false, {}}, {true, {{0, 0.0f}, {1, 0.5f}}}}};
    ASSERT_EQ(
        nlohmann::json(a).dump(),
        R"({"answers":{"request000":{"result":false},"request001":{"relevance":[{"docid":0,"rank":0.0},{"docid":1,"rank":0.5}],"result":true}}})");
}
