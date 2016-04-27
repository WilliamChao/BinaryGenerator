#pragma once
namespace bg {

enum SectionType;
enum SymbolType;
enum RelocationType;

class Context;
class Section;
class Symbol;
class SymbolTable;
class Relocation;
class RelocationTable;
class String;
class StringTable;


class Context
{
public:
    Context();

    Section&            getText();
    Section&            getIData();
    Section&            getUData();
    RelocationTable&    getRelocTable();
    SymbolTable&        getSymbolTable();
    StringTable&        getStringTable();

    bool writeCOFFx86(std::ostream &os);
    bool writeCOFFx86_64(std::ostream &os);
    bool writeELFx86(std::ostream &os);
    bool writeELFx86_64(std::ostream &os);

private:
    typedef std::unique_ptr<Section>            SectionPtr;
    typedef std::unique_ptr<SymbolTable>        SymbolTablePtr;
    typedef std::unique_ptr<RelocationTable>    RelocationTablePtr;
    typedef std::unique_ptr<StringTable>        StringTablePtr;

    SectionPtr          m_text;
    SectionPtr          m_idata;
    SectionPtr          m_udata;
    SymbolTablePtr      m_sym;
    RelocationTablePtr  m_reloc;
    StringTablePtr      m_str;
};

} // namespace bg