#ifndef JSONCOMMANDS_H
#define JSONCOMMANDS_H


class JsonCommands : public JsonObject
{
    public:
        JsonCommands();
        void Execute(std::string filename);
        std::vector<std::string> getRequiredKeys();
        virtual ~JsonCommands();
    protected:
    private:

};

#endif // JSONCOMMANDS_H
