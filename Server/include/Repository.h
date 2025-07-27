#pragma once

#include "IRepository.h"

class Repository : public IRepository {
public:
    Repository( std::shared_ptr<spdlog::logger> &file_logger, std::shared_ptr<spdlog::logger> &cdr_logger ) : IRepository( file_logger, cdr_logger ) { }

    void add_session( const std::string & ) override;
    bool remove_session( const std::string & ) override;
    bool is_session_active( const std::string & ) override;
    void cleanup_expired_sessions( const uint8_t & ) override;
    bool graceful_shutdown( const uint8_t &) override;

private:
};