#pragma once

#include <vector>

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include "kdlib/typeinfo.h"
#include "kdlib/variant.h"
#include "kdlib/dataaccessor.h"

namespace kdlib {

///////////////////////////////////////////////////////////////////////////////

class TypedVar;
typedef boost::shared_ptr<TypedVar>  TypedVarPtr;
typedef std::vector<TypedVarPtr> TypedVarList;

class TypedValue;
typedef std::vector<TypedValue>  TypedValueList;

class TypedVarScope;
typedef boost::shared_ptr<TypedVarScope>  TypedVarScopePtr;

class StackFrame;
typedef boost::shared_ptr<StackFrame>  StackFramePtr;


///////////////////////////////////////////////////////////////////////////////

TypedVarPtr loadTypedVar( const std::wstring &varName );

TypedVarPtr loadTypedVar( const std::wstring &typeName, MEMOFFSET_64 addr );

TypedVarPtr loadTypedVar( const TypeInfoPtr &typeInfo, MEMOFFSET_64 addr );

TypedVarPtr loadTypedVar( SymbolPtr &symbol );

TypedVarPtr loadTypedVar( const std::wstring &typeName, DataAccessorPtr& dataSource);

TypedVarPtr loadTypedVar( const TypeInfoPtr &typeInfo, DataAccessorPtr& dataSource);

TypedVarPtr loadTypedVar( const std::wstring &funcName, const std::wstring &prototype);

TypedVarPtr containingRecord( MEMOFFSET_64 addr, const std::wstring &typeName, const std::wstring &fieldName );

TypedVarPtr containingRecord( MEMOFFSET_64 addr, TypeInfoPtr &typeInfo, const std::wstring &fieldName );

TypedVarList loadTypedVarList( MEMOFFSET_64 addr, const std::wstring &typeName, const std::wstring &fieldName );

TypedVarList loadTypedVarList( MEMOFFSET_64 addr, TypeInfoPtr &typeInfo, const std::wstring &fieldName );

TypedVarList loadTypedVarArray( MEMOFFSET_64 addr, const std::wstring &typeName, size_t count );

TypedVarList loadTypedVarArray( MEMOFFSET_64 addr, TypeInfoPtr &typeInfo, size_t count );

TypedVarPtr loadCharVar( char var );
TypedVarPtr loadShortVar( short var );
TypedVarPtr loadLongVar( long var );
TypedVarPtr loadLongLongVar( long long var );

TypedVarPtr loadUCharVar( unsigned char var );
TypedVarPtr loadUShortVar( unsigned short var );
TypedVarPtr loadULongVar( unsigned long var );
TypedVarPtr loadULongLongVar( unsigned long long var );

TypedVarPtr loadIntVar( int var );
TypedVarPtr loadUIntVar( unsigned int var );
TypedVarPtr loadBoolVar( bool var );
TypedVarPtr loadFloatVar( float var );
TypedVarPtr loadDoubleVar( double var );
TypedVarPtr loadWCharVar( wchar_t var );

class TypedVar :  public NumBehavior {

    friend TypedVarPtr loadTypedVar( const SymbolPtr &symbol );

    friend TypedVarPtr loadTypedVar( const std::wstring &varName );

    friend TypedVarPtr loadTypedVar( const std::wstring &typeName, MEMOFFSET_64 addr );

    friend TypedVarPtr loadTypedVar( const TypeInfoPtr &typeInfo, MEMOFFSET_64 addr );

    friend TypedVarPtr loadTypedVar( const std::wstring &typeName, DataAccessorPtr& dataSource );

    friend TypedVarPtr loadTypedVar( const TypeInfoPtr &typeInfo, DataAccessorPtr& dataSource );

    friend TypedVarPtr loadTypedVar( const std::wstring &funcName, const std::wstring &prototype);

public:
    
    virtual std::wstring str() = 0;
    virtual VarStorage getStorage() const = 0;
    virtual std::wstring  getRegisterName() const = 0;
    virtual MEMOFFSET_64 getAddress() const = 0;
    virtual MEMOFFSET_64 getDebugStart() const = 0;
    virtual MEMOFFSET_64 getDebugEnd() const = 0;
    virtual size_t getSize() const = 0;
    virtual std::wstring getName() const = 0;
    virtual TypedVarPtr getElement( const std::wstring& fieldName ) = 0;
    virtual TypedVarPtr getElement( size_t index ) = 0;
    virtual VarStorage getElementStorage(const std::wstring& fieldName) = 0;
    virtual VarStorage getElementStorage(size_t index ) = 0;
    virtual MEMOFFSET_REL getElementOffset(const std::wstring& fieldName ) = 0;
    virtual MEMOFFSET_REL getElementOffset(size_t index ) = 0;
    virtual RELREG_ID getElementOffsetRelativeReg(const std::wstring& fieldName ) = 0;
    virtual RELREG_ID getElementOffsetRelativeReg(size_t index ) = 0;
    virtual unsigned long getElementReg(const std::wstring& fieldName) = 0;
    virtual unsigned long getElementReg(size_t index) = 0;
    virtual size_t getElementCount() = 0;
    virtual std::wstring getElementName( size_t index ) = 0;
    virtual size_t getElementIndex(const std::wstring&  elementName) = 0;
    virtual TypedVarPtr getMethod( const std::wstring &name, const std::wstring&  prototype = L"") = 0;
    virtual TypedVarPtr getMethod( const std::wstring &name, TypeInfoPtr prototype) = 0;
    virtual TypeInfoPtr getType() const = 0;
    virtual NumVariant getValue() const = 0;
    virtual TypedVarPtr deref() = 0;
    virtual TypedVarPtr castTo(const std::wstring& typeName) = 0;
    virtual TypedVarPtr castTo(const TypeInfoPtr &typeInfo) = 0;
    virtual void writeBytes(DataAccessorPtr& stream, size_t bytes = 0) const = 0;
    virtual TypedValue call(const TypedValueList& arglst) = 0;
    //virtual TypedVarPtr getVTBL(const std::wstring& baseClass=L"") = 0;

protected:

    TypedVar() 
    {}

    virtual ~TypedVar() 
    {}
};

///////////////////////////////////////////////////////////////////////////////

class TypedValue : public NumBehavior
{
public:
    TypedValue();

    TypedValue(const TypedVarPtr& var) : m_value(var){}
    TypedValue(const NumVariant& var );

    TypedValue( char var ) : m_value( loadCharVar(var) ) {}
    TypedValue( short var) : m_value( loadShortVar(var) ) {}
    TypedValue( long var ) : m_value( loadLongVar(var) ) {}
    TypedValue( long long var ) : m_value( loadLongLongVar(var) ) {}

    TypedValue( unsigned char var ) : m_value( loadUCharVar(var) ) {}
    TypedValue( unsigned short var) : m_value( loadUShortVar(var) ) {}
    TypedValue( unsigned long var ) : m_value( loadULongVar(var) ) {}
    TypedValue( unsigned long long var ) : m_value( loadULongLongVar(var) ) {}

    TypedValue( int var ) : m_value( loadIntVar(var) ) {}
    TypedValue( unsigned int var ) : m_value( loadIntVar(var) ) {}

    TypedValue( float var ) : m_value( loadFloatVar(var) ) {}
    TypedValue( double var ) : m_value( loadDoubleVar(var) ) {}
    TypedValue( wchar_t var ) : m_value( loadWCharVar(var) ) {}
    TypedValue( bool var ) : m_value( loadBoolVar(var) ) {}

public:

    std::wstring str() {
        return m_value->str();
    }

    VarStorage getStorage() const {
        return m_value->getStorage();
    }

    std::wstring  getRegisterName() const {
        return m_value->getRegisterName();
    }

    MEMOFFSET_64 getAddress() const {
        return m_value->getAddress();
    }

    MEMOFFSET_64 getDebugStart() const {
        return m_value->getDebugStart();
    }

    MEMOFFSET_64 getDebugEnd() const {
        return m_value->getDebugEnd();
    }

    size_t getSize() const {
        return m_value->getSize();
    }

    std::wstring getName() const {
        return m_value->getName();
    }

    TypedVarPtr getElement( const std::wstring& fieldName ) {
        return m_value->getElement(fieldName);
    }

    TypedVarPtr getElement( size_t index ) {
        return m_value->getElement(index);
    }

    VarStorage getElementStorage(const std::wstring& fieldName) {
        return m_value->getElementStorage(fieldName);
    }

    VarStorage getElementStorage(size_t index ) {
        return m_value->getElementStorage(index);
    }

    MEMOFFSET_REL getElementOffset(const std::wstring& fieldName ) {
        return m_value->getElementOffset(fieldName);
    }

    MEMOFFSET_REL getElementOffset(size_t index ) {
        return m_value->getElementOffset(index);
    }

    RELREG_ID getElementOffsetRelativeReg(const std::wstring& fieldName ) {
        return m_value->getElementOffsetRelativeReg(fieldName);
    }

    RELREG_ID getElementOffsetRelativeReg(size_t index ) {
        return m_value->getElementOffsetRelativeReg(index);
    }

    unsigned long getElementReg(const std::wstring& fieldName) {
        return m_value->getElementReg(fieldName);
    }

    unsigned long getElementReg(size_t index) {
        return m_value->getElementReg(index);
    }

    size_t getElementCount() {
        return m_value->getElementCount();
    }

    std::wstring getElementName( size_t index ) {
        return m_value->getElementName(index);
    }

    size_t getElementIndex(const std::wstring&  elementName) {
        return m_value->getElementIndex(elementName);
    }

    TypeInfoPtr getType() const {
        return m_value->getType();
    }

    NumVariant getValue() const {
        return m_value->getValue();
    }

    TypedVarPtr deref() {
        return m_value->deref();
    }

    TypedVarPtr castTo(const std::wstring& typeName) {
        return m_value->castTo(typeName);
    }

    TypedVarPtr castTo(const TypeInfoPtr &typeInfo) {
        return m_value->castTo(typeInfo);
    }

    void writeBytes(DataAccessorPtr& stream, size_t bytes = 0) const {
        return m_value->writeBytes(stream, bytes);
    }

    TypedValue call(const TypedValueList& arglst) {
        return m_value->call(arglst);
    }
    
private:
    TypedVarPtr  m_value;
};

///////////////////////////////////////////////////////////////////////////////

} // end kdlib namespace
