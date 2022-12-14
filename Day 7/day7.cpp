#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <queue>
using namespace std;

class File
{
public:
    const int size;
    const string name;

    File(const string &_name, const int _size) : name(_name), size(_size) {}
};

class Folder
{
public:
    int size = -1;
    const string foldername;

    unordered_map<string, shared_ptr<File>> files;
    unordered_map<string, shared_ptr<Folder>> subfolders;

    shared_ptr<Folder> parent;

    Folder(
        const string &_filename,
        const shared_ptr<Folder> _parent) : foldername(_filename), parent(_parent)
    {
        this->files.reserve(5);
        this->subfolders.reserve(5);
    };

    int getSize()
    {
        int currSize = 0;

        // File calc
        for (auto &[name, file] : this->files)
        {
            currSize += file->size;
        }

        // Folder calc
        for (auto &[name, subfolder] : this->subfolders)
        {
            if (subfolder->size < 0)
            {
                currSize += subfolder->getSize();
            }
            else
            {
                currSize += subfolder->size;
            }
        }

        this->size = currSize;

        return this->size;
    }

    bool subFolderExists(const string &name)
    {
        return this->subfolders.contains(name);
    }

    bool fileExists(const string &name)
    {
        return this->files.contains(name);
    }
};

// Debug
void printFoldersTree(shared_ptr<Folder> root, int indent = 0)
{
    cout << string(indent, '\t') << "- " << root->foldername << " (dir, size=" << root->size << ")\n";
    for (auto &[name, subfolder] : root->subfolders)
    {
        printFoldersTree(subfolder, indent + 1);
    }
    for (auto &[name, file] : root->files)
    {
        cout << string(indent + 1, '\t') << "> " << file->name << " (file, size=" << file->size << ")\n";
    }
}

int part1(shared_ptr<Folder> root)
{
    // BFS
    int s = 0;
    queue<shared_ptr<Folder>> q;
    q.push(root);

    while (!q.empty())
    {
        auto currFolder = q.front();
        q.pop();
        if (currFolder->size <= 100000)
            s += currFolder->size;
        for (auto [_, f] : currFolder->subfolders)
            q.push(f);
    }
    return s;
}

int part2(shared_ptr<Folder> root)
{
    // BFS
    int totalMemory = 70000000;
    int requiredMemory = 30000000;
    int currentMemory = root->size;
    int freeingMemory = requiredMemory - (totalMemory - currentMemory);

    int s = 70000000;
    queue<shared_ptr<Folder>> q;
    q.push(root);

    while (!q.empty())
    {
        auto currFolder = q.front();
        q.pop();
        if (currFolder->size >= freeingMemory)
            s = min(s, currFolder->size);
        for (auto [_, f] : currFolder->subfolders)
            q.push(f);
    }
    return s;
}

int main()
{
    fstream inputFile("day7.input.txt");
    string line;

    auto rootFolder = make_shared<Folder>("/", nullptr);
    auto cursor = rootFolder;

    while (getline(inputFile, line))
    {
        // Command
        auto stream = istringstream(line);
        if (line[0] == '$')
        {
            string _, arg;
            if (stream >> _ >> _ >> arg)
            {
                if (arg == "..")
                {
                    cursor = cursor->parent;
                }
                else if (arg == "/")
                {
                    cursor = rootFolder;
                }
                // Add a new folder
                else
                {
                    if (!cursor->subFolderExists(arg))
                    {
                        auto newFolder = make_shared<Folder>(arg, cursor);
                        cursor->subfolders[arg] = newFolder;
                        cursor = newFolder;
                    }
                    else
                    {
                        cursor = cursor->subfolders[arg];
                    }
                }
            }
        }
        else
        {
            string arg1, arg2;
            stream >> arg1 >> arg2;
            if (arg1 == "dir")
            {
                if (!cursor->subFolderExists(arg2))
                {
                    auto newFolder = make_shared<Folder>(arg2, cursor);
                    cursor->subfolders[arg2] = newFolder;
                }
            }
            else
            {
                int _size = stoi(arg1);
                if (!cursor->fileExists(arg2))
                {
                    auto newFile = make_shared<File>(arg2, _size);
                    cursor->files[arg2] = newFile;
                }
            }
        }
    }

    // Initialize all folder size
    rootFolder->getSize();

    cout << part2(rootFolder);
}