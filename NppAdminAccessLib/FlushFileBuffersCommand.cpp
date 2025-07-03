#include "FlushFileBuffersCommand.hpp"
#include "Common.hpp"
#include "IWinApiFunctions.hpp"

class FlushFileBuffersCommand : public ICommand {
public:
  using ICommand::ICommand;
private:
  bool execute(const std::vector<char>& data,
               std::vector<char>& ret_data) override {
    auto in = get_command_data_from_vector<FlushFileBuffersData>(data);
    if (!in) return false;
    auto out = prepare_vector_to_store_data<FlushFileBuffersResult>(ret_data);
    out->success    = m_winapi.flush_file_buffers(in->handle);
    out->last_error = GetLastError();
    return true;
  }
};

std::unique_ptr<ICommand> make_flush_file_buffers_command(IWinApiFunctions& winapi) {
  return std::make_unique<FlushFileBuffersCommand>(winapi);
}
