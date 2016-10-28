#ifndef JSONOBJECT_H
#define JSONOBJECT_H


class JsonObject
{
    public:
        JsonObject();
        void Parse(std::string filename);
        virtual void Execute(std::string filename);
        virtual void ExecuteExport(std::string filename);
        virtual std::vector<std::string> getRequiredKeys();
        void Write(std::string filename);
        virtual ~JsonObject();
    protected:
        jsoncons::json j;
        bool Error = false;
    private:

};

#endif // JSONOBJECT_H
