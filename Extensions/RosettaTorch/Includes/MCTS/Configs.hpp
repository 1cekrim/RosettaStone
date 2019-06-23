// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_CONFIGS_HPP
#define ROSETTASTONE_TORCH_MCTS_CONFIGS_HPP

namespace RosettaTorch::MCTS
{
namespace Policy
{
}

namespace Configs
{
constexpr int CREDIT_GRANULARITY = 100;

namespace UpdaterPolicy
{
struct TreeUpdate
{
    // Do nothing
};
struct LinearUpdate
{
    // Do nothing
};
}  // namespace UpdaterPolicy

using UpdatePolicy = UpdaterPolicy::TreeUpdate;

static constexpr bool RECORD_LEADING_NODES =
    std::is_same_v<UpdatePolicy, UpdaterPolicy::TreeUpdate>;

}  // namespace Configs
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_CONFIGS_HPP