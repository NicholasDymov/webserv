#ifndef URI_HPP
# define URI_HPP

# include <string>

namespace http {

    class Uri {
    public:
        Uri();
        Uri(const std::string &rawUri);
        Uri(const Uri &other);
        ~Uri();

        Uri &operator=(const Uri &other);

        const std::string& getRaw() const;
        const std::string& getPath() const;
        const std::string& getQuery() const;
        const std::string& getFragment() const;

        static std::string decode(const std::string &str);
        static std::string sanitize(const std::string &path);

    private:
        std::string raw;
        std::string path;
        std::string query;
        std::string fragment;

        void parse();
    };

} // namespace http

#endif
