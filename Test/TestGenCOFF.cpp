#include "../BinaryGenerator.h"

void Generate_COFF_x86()
{
    // void SayHello() { puts("hello!"); }
    const char string[] = "hello!";
    const char code[] = "\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3";
    const char name[] = "_SayHello";

    bg::IContext *ctx = bg::CreateContext();
    bg::ISection *text = ctx->createSection(".text", bg::SectionType_Text);
    bg::Symbol sym_str  = text->addStaticSymbol(string, sizeof(string), "$hello");
    bg::Symbol sym_code = text->addExternalSymbol(code, sizeof(code), name);
    text->addRelocation(sym_code.addr + 1, "$hello", bg::RelocationType_ADDR32);
    text->addRelocation(sym_code.addr + 6, "_puts", bg::RelocationType_REL32);

    ctx->write("SayHello_x86.obj", bg::Format_PECOFF_x86_Obj);
    ctx->release();
}

void Generate_COFF_x64()
{
    // void SayHello() { puts("hello!"); }
    const char string[] = "hello!";
    const char code[] = "\x48\x8D\x0D\x00\x00\x00\x00\xE9\x00\x00\x00\x00";
    const char name[] = "SayHello";

    bg::IContext *ctx = bg::CreateContext();
    bg::ISection *text = ctx->createSection(".text", bg::SectionType_Text);
    bg::Symbol sym_str  = text->addStaticSymbol(string, sizeof(string), "$hello");
    bg::Symbol sym_code = text->addExternalSymbol(code, sizeof(code), name);
    text->addRelocation(sym_code.addr + 3, "$hello", bg::RelocationType_REL32);
    text->addRelocation(sym_code.addr + 8, "puts", bg::RelocationType_REL32);

    ctx->write("SayHello_x64.obj", bg::Format_PECOFF_x64_Obj);
    ctx->release();
}

void Generate_PE_x86()
{
    // void SayHello() { MessageBoxA("hello!"); }
    const char code[] = "\x55\x8B\xEC\x83\xEC\x34\x53\x56\x57\xC7\x45\xD8\x75\x73\x65\x72\xC7\x45\xDC\x33\x32\x2E\x64\xC7\x45\xE0\x6C\x6C\x00\x00\xC7\x45\xCC\x4D\x65\x73\x73\xC7\x45\xD0\x61\x67\x65\x42\xC7\x45\xD4\x6F\x78\x41\x00\xC7\x45\xE4\x68\x65\x6C\x6C\xC7\x45\xE8\x6F\x21\x00\x00\x33\xC9\x64\x8B\x35\x30\x00\x00\x00\x8B\x76\x0C\x8B\x76\x1C\x8B\x46\x08\x8B\x7E\x20\x8B\x36\x38\x4F\x18\x75\xF3\x89\x45\xF8\x8B\x55\xF8\x8B\x42\x3C\x8B\x44\x10\x78\x83\x65\xFC\x00\x03\xC2\x8B\x70\x20\x8B\x78\x24\x8B\x58\x1C\x8B\x40\x14\x03\xF2\x03\xFA\x03\xDA\x89\x45\xF4\x85\xC0\x74\x36\x8B\x45\xFC\x8B\x0C\x86\x0F\xB7\x04\x47\x8B\x04\x83\x03\xC2\x81\x7C\x11\x08\x61\x72\x79\x41\x75\x05\x89\x45\xF0\xEB\x0D\x81\x7C\x11\x04\x72\x6F\x63\x41\x75\x03\x89\x45\xEC\xFF\x45\xFC\x8B\x45\xFC\x3B\x45\xF4\x72\xCA\x8D\x45\xD8\x50\xFF\x55\xF0\x8D\x4D\xCC\x51\x50\xFF\x55\xEC\x6A\x00\x8D\x4D\xE4\x51\x51\x6A\x00\xFF\xD0\x5F\x5E\x5B\xC9\xC3";
    const char name[] = "_SayHello";

    bg::IContext *ctx = bg::CreateContext();
    bg::ISection *text = ctx->createSection(".text", bg::SectionType_Text);
    text->addExternalSymbol(code, sizeof(code), name);
    ctx->setEntryPoint(name);
    ctx->addDLLExport(name);

    ctx->write("SayHello_x86.exe", bg::Format_PECOFF_x86_Exe);
    ctx->write("SayHello_x86.dll", bg::Format_PECOFF_x86_DLL);
    ctx->release();
}


void Generate_PE_x64()
{
    // void SayHello() { MessageBoxA("hello!"); }
    const char code[] = "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x48\x89\x7C\x24\x20\x55\x48\x8B\xEC\x48\x83\xEC\x40\xC7\x45\xE0\x75\x73\x65\x72\x45\x33\xD2\xC7\x45\xE4\x33\x32\x2E\x64\xC7\x45\xE8\x6C\x6C\x00\x00\xC7\x45\xF0\x4D\x65\x73\x73\xC7\x45\xF4\x61\x67\x65\x42\xC7\x45\xF8\x6F\x78\x41\x00\xC7\x45\x10\x68\x65\x6C\x6C\xC7\x45\x14\x6F\x21\x00\x00\x65\x48\x8B\x04\x25\x60\x00\x00\x00\x48\x8B\x48\x18\x48\x8B\x51\x20\x48\x8B\x42\x50\x66\x44\x39\x50\x18\x74\x11\x48\x8B\x12\x48\x8B\x12\x48\x8B\x42\x50\x66\x44\x39\x50\x18\x75\xF2\x4C\x8B\x42\x20\x48\x8B\x5D\x10\x49\x63\x40\x3C\x42\x8B\x8C\x00\x88\x00\x00\x00\x49\x03\xC8\x8B\x51\x20\x44\x8B\x49\x24\x49\x03\xD0\x8B\x71\x1C\x4D\x03\xC8\x49\x03\xF0\x44\x39\x51\x14\x4C\x8B\x55\x10\x76\x3B\x8B\x79\x14\x41\x0F\xB7\x01\x44\x8B\x1A\x8B\x0C\x86\x49\x03\xC8\x43\x81\x7C\x03\x08\x61\x72\x79\x41\x75\x05\x4C\x8B\xD1\xEB\x0D\x43\x81\x7C\x03\x04\x72\x6F\x63\x41\x48\x0F\x44\xD9\x48\x83\xC2\x04\x49\x83\xC1\x02\x48\x83\xEF\x01\x75\xC8\x48\x8D\x4D\xE0\x41\xFF\xD2\x48\x8D\x55\xF0\x48\x8B\xC8\xFF\xD3\x45\x33\xC9\x4C\x8D\x45\x10\x48\x8D\x55\x10\x33\xC9\xFF\xD0\x48\x8B\x5C\x24\x58\x48\x8B\x74\x24\x60\x48\x8B\x7C\x24\x68\x48\x83\xC4\x40\x5D\xC3";
    const char name[] = "SayHello";

    bg::IContext *ctx = bg::CreateContext();
    bg::ISection *text = ctx->createSection(".text", bg::SectionType_Text);
    text->addExternalSymbol(code, sizeof(code), name);
    ctx->setEntryPoint(name);
    ctx->addDLLExport(name);

    ctx->write("SayHello_x64.exe", bg::Format_PECOFF_x64_Exe);
    ctx->write("SayHello_x64.dll", bg::Format_PECOFF_x64_DLL);
    ctx->release();
}


int main(int argc, char *argv[])
{
    Generate_COFF_x86();
    Generate_COFF_x64();
    Generate_PE_x86();
    Generate_PE_x64();
}
