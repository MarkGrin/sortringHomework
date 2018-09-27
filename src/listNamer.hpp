#ifndef H_B0626EFF118D4E97A9807E93AC09F188

#define H_B0626EFF118D4E97A9807E93AC09F188

#include <vector>
#include <string>

class ListNamer
{
    ListNamer () = delete;

    std::vector<std::string> names_;

    public:

    ListNamer (const char* fileName);

    std::string getNextName () const;
};

#endif /* H_B0626EFF118D4E97A9807E93AC09F188 */

