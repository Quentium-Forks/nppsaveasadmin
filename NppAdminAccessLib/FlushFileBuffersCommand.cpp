#include "ICommand.hpp"
#include "FlushFileBuffersCommand.hpp"
#include "IWinApiFunctions.hpp"
#include <cstring>

class FlushFileBuffersCommand : public ICommand {
  public:
    explicit FlushFileBuffersCommand(IWinApiFunctions& winapi)
        : ICommand(winapi) {}

    bool execute(const std::vector<char>& in_buffer, std::vector<char>& out_buffer) override {
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
};

std::shared_ptr<ICommand> make_flush_file_buffers_command(IWinApiFunctions& winapi) {
    return std::make_shared<FlushFileBuffersCommand>(winapi);
}
