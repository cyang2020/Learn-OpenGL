class Shader{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    std::string vertexCode;
    std::string fragmentCode;
    const char* vertexShaderCode;
    const char* fragmentShaderCode;
    unsigned int ID;
    void use();
    void setBoolUni(const std::string &name, bool value);
    void setIntUni(const std::string &name, int value);
    void setFloatUni(const std::string &name, float value);
//    ~Shader();
};
