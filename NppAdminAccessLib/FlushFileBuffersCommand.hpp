#pragma once

#include "ICommand.hpp"
#include "IWinApiFunctions.hpp"

std::unique_ptr<ICommand> make_flush_file_buffers_command(IWinApiFunctions& winapi);
