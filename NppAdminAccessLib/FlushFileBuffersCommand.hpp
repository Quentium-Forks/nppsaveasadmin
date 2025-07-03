#pragma once

#include "ICommand.hpp"
#include "IWinApiFunctions.hpp"
#include "Common.hpp"
#include <memory>

std::shared_ptr<ICommand> make_flush_file_buffers_command(IWinApiFunctions& winapi);

class FlushFileBuffersCommand : public ICommand {
public:
    explicit FlushFileBuffersCommand(IWinApiFunctions& winapi)
        : ICommand(winapi) {}

    bool execute(const std::vector<char>& in_buffer, std::vector<char>& out_buffer) override;

private:
    // No need to store m_winapi here, it's already in ICommand
};
