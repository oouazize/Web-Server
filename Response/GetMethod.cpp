#include "../Client_Gymir.hpp"
#include "../Server_Master.hpp"

int Response::GetMethod(Client_Gymir* & Client, Server_Master& Server, std::string OldPath) {
    StatusCode = getResourcePath(Server.conf);
    if (StatusCode != 200) return StatusCode;
    if (getResourceType()) { // if it's directory
        StatusCode = IsURIHasSlashAtTheEnd(OldPath);
        if (StatusCode != 200) return StatusCode;
        if (Server.conf.Servers[LocationIndex->first].Locations[LocationIndex->second]->AutoIndex == "on") {
            StatusCode = autoindex(Path.c_str());
            return StatusCode;
        }
        StatusCode = IsDirHaveIndexFiles(Server.conf);
        if (StatusCode != 200) return StatusCode;
    }
    StatusCode = HandleCGIprogram(Client, Server);
    return StatusCode;
}

int Response::autoindex(const char *dirpath) {
    DIR *dir;
    struct stat result;
    struct dirent *entry;
    std::ostringstream out;
    dir = opendir(dirpath);
    if (dir == NULL) {
        printf("Error: could not open directory\n");
        return 404;
    }
    std::ofstream outfile ("autoindex.html");
    std::string Text;
    out << "<html>\n<head><title>Index of ";
    out << dirpath;
    out << "</title></head>\n""<body>\n<h1>Index of ";
    out << dirpath;
    out << "</h1><hr><pre>";
    readdir(dir);
    readdir(dir);
    while ((entry = readdir(dir)) != NULL) {
        out << "<a href=\"";
        out << entry->d_name;
        out << "\">";
        Text.clear();
        Text.append(entry->d_name, 0, 41);
        out << Text;
        Text.clear();
        if (strlen(entry->d_name) > 41) out << "...";
        out << "</a>";
        if (strlen(entry->d_name) > 41) Text.append(7, ' ');
        else Text.append(51 - strlen(entry->d_name), ' ');
        out << Text;
        std::string PathOF = dirpath;
        PathOF.append(entry->d_name);
        if(stat(PathOF.c_str(), &result) == 0) {
            std::string Size;
            time_t mod_time = result.st_ctime;
            Text = asctime(gmtime(&mod_time));
            Text.erase(--Text.end());
            Text.append(14, ' ');
            out << Text;
            if (S_ISREG(result.st_mode))
                out << result.st_size;
            else
                out << "-";
        }
        out << "\n";
    }
    out << "</pre><hr></body>\n</html>\n";
    outfile << out.str();
    outfile.close();
    Path = "autoindex.html";
    closedir(dir);
    return 200;
}