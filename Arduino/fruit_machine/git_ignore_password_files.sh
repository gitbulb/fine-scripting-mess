# The following files contain sensitive data, passwords or API keys.
# Tell Git to ignore changes (added passwords or API keys) to these files.
git update-index --skip-worktree my_wifi_credentials.hpp
git update-index --skip-worktree my_weather_config.hpp

# Re-enable tracking of these files.
# git update-index --no-skip-worktree my_wifi_credentials.hpp
# git update-index --no-skip-worktree my_weather_config.hpp
