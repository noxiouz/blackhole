#include "Mocks.hpp"

namespace testing {

enum level : std::uint8_t { debug, info, warn, error };

} // namespace testing

namespace blackhole { namespace sink {

template<>
struct priority_traits<testing::level> {
    static inline
    priority_t map(testing::level lvl) {
        switch (lvl) {
        case testing::level::debug:
            return priority_t::debug;
        case testing::level::info:
            return priority_t::info;
        case testing::level::warn:
            return priority_t::warning;
        case testing::level::error:
            return priority_t::err;
        }
    }
};

} } // namespace blackhole::sink

TEST(Functional, SyslogConfiguredVerboseLogger) {
    verbose_logger_t<testing::level> log;

    typedef formatter::string_t formatter_type;
    typedef sink::syslog_t<testing::level> sink_type;

    auto formatter = std::make_unique<formatter_type>("%(message)s [%(...L)s]");
    auto sink = std::make_unique<sink_type>("testing");
    auto frontend = std::make_unique<frontend_t<formatter_type, sink_type, testing::level>>(std::move(formatter), std::move(sink));
    log.add_frontend(std::move(frontend));

    log::record_t record = log.open_record(level::error);
    if (record.valid()) {
        record.attributes["message"] = { utils::format("Some message from: '%s'!", "Hell"), log::attribute::scope::event };
        log.push(std::move(record));
    }
}