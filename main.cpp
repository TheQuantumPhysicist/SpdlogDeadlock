#include "defaultlogger.h"
#include <boost/filesystem.hpp>
#include <codecvt> // std::codecvt_utf8
#include <iostream>
#include <locale>
#include <string>
#include <thread>
#include <chrono>

std::string PossiblyWideStringToString(const std::string& str) { return str; }

std::string PossiblyWideStringToString(const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<std::wstring::value_type>, std::wstring::value_type> cv;
    return cv.to_bytes(str);
}

void InitLogging()
{
    const boost::filesystem::path LogFilesDir = boost::filesystem::current_path();
    if (!boost::filesystem::is_directory(LogFilesDir)) {
        boost::filesystem::create_directories(boost::filesystem::current_path());
    }
    const boost::filesystem::path LogFilePath = boost::filesystem::current_path() / "test.log";

    const bool isDebugMode = false;
    const bool rotateFile  = true;

    // max file size
    const std::size_t maxSize = 1 << 30;

    // max rotated files
    const std::size_t maxFiles = 5;

    const b_sev minSeverity = isDebugMode ? b_sev::debug : b_sev::info;

    NLog.set_level(minSeverity);

    const bool logFileAddingResult = NLog.add_rotating_file(
        PossiblyWideStringToString(LogFilePath.native()), maxSize, maxFiles, rotateFile, minSeverity);
    if (!logFileAddingResult) {
        throw std::runtime_error("Failed to open log file for writing: " +
                                 PossiblyWideStringToString(LogFilePath.native()));
    }

    NLog.write(b_sev::info, "\n\n\n\n\n\n\n\n\n\n---------------------------------");

    NLog.write(b_sev::info, "Initialized logging successfully!");
}

int main()
{
    InitLogging();
    NLog.write(b_sev::info, "Started!");
    for(int i = 0; ; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        NLog.write(b_sev::info, "{} more!", i);
    }
    return 0;
}
