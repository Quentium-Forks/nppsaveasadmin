#include "FlushFileBuffersCommand.hpp"
#include <cstring>

// Factory function implementation
std::shared_ptr<ICommand> make_flush_file_buffers_command(IWinApiFunctions& winapi) {
    return std::make_shared<FlushFileBuffersCommand>(winapi);
}

bool FlushFileBuffersCommand::execute(const std::vector<char>& in_buffer, std::vector<char>& out_buffer) {
    // Data structures must match those used in FuncExecutor.cpp
    struct FlushFileBuffersData {
        HANDLE handle;
    };
    struct FlushFileBuffersResult {
        BOOL success;
        DWORD last_error;
    };

    if (in_buffer.size() != sizeof(FlushFileBuffersData)) {
        return false;
    }

    FlushFileBuffersData data;
    std::memcpy(&data, in_buffer.data(), sizeof(data));

    FlushFileBuffersResult result = {0};
    result.success = m_winapi.FlushFileBuffers(data.handle);
    result.last_error = GetLastError();

    out_buffer.resize(sizeof(result));
    std::memcpy(out_buffer.data(), &result, sizeof(result));

    return true;
}

BOOL WinApiFunctions::FlushFileBuffers(HANDLE hFile) {
    return ::FlushFileBuffers(hFile);
}
