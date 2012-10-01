#include <map>

namespace traits
{

//! Trait with two types; use both in typedef
/*!
 * Raw template types are always CamelCase with two leading underscores
 * Multiple template types in a template declaration are split across multiple lines
 */
template
<
    class __SomeKey,
    class __SomeType
>
struct some_trait
{
    //! Trait types are always snake_case
    typedef __SomeKey key_type;
    typedef __SomeType value_type;
    typedef std::map<key_type, value_type> storage_type;

    //! Trait values are always snake_case
    static const int some_value = 5;
};

// #############################################################################################################################################

//! Specialization for only one type; use type as value type, and default to string for key type
template<class __SomeType>
struct some_trait
<
    std::string,
    __SomeType
>
{
    typedef std::string key_type;
    typedef __SomeType value_type;
    typedef std::map<key_type, value_type> storage_type;

    //! Trait values are always snake_case
    static const int some_value = 5;
};

} // traits



// ## Normal Class #############################################################################################################################

class SomeBaseClass
{
public:
    SomeBaseClass()
    {
        //
    }

    SomeBaseClass( SomeBaseClass const & other )
    {
        //
    }
};

// pound signs are used as primary separators, ie between classes, with optional inline titles
// ## Normal Class #############################################################################################################################

//! A normal class with no template functions
class NormalClass : public SomeBaseClass
{
public:
    //! Type for our storage
    /*!
     * Typedefs derived from other types are CamelCase with a single leading underscore
     */
    typedef traits::some_trait<int>::type _Storage;

protected:
    //! Storage member variable to hold our data
    /*!
     * Member variables have a single trailing underscore
     */
    _Storage storage_;

public:
    // equal signs are used as secondary separators, ie between functions
    // =========================================================================================================================================
    //! Default constructor
    NormalClass()
    {
        //
    }

    // =========================================================================================================================================
    //! Copy constructor
    /*!
     * Base class constructors and member variable initializations are placed one per line, indented from the constructor
     */
    NormalClass( NormalClass const & other )
    :
        SomeBaseClass( other ),
        storage_( other.storage_ )
    {
        //
    }

    // =========================================================================================================================================
    //! Perform some useful operation
    /*!
     * Function names are camelCase after the first letter
     * Parameter names are snake_case with no trailing underscores
     */
    void doSomething( std::string const & some_key, int const & some_value )
    {
        storage_[some_key] = some_value;
    }
};

// #############################################################################################################################################

//! A class with some template functions
class TemplateFunctionClass
{
    //! Type for our storage
    /*!
     * Note that this results in a map from int to std::string
     */
    typedef traits::some_trait<int, std::string> _StorageTrait;
    typedef _StorageTrait::type _Storage;

protected:
    //! Storage member variable to hold our data
    _Storage storage_;

public:
    // =========================================================================================================================================
    //! Default constructor
    TemplateFunctionClass()
    {
        //
    }

    // =========================================================================================================================================
    //! Copy constructor
    TemplateFunctionClass( TemplateFunctionClass const & other )
    :
        storage_( other.storage_ )
    {
        //
    }

    // =========================================================================================================================================
    //! If the given key is an arithmetic type (ie numeric), cast it to our key type and continue as usual
    template
    <
        class __SomeType,
        typename std::enable_if<std::is_arithmetic<__SomeType>::value, int>::type = 0
    >
    void doSomething( __SomeType const & some_key, _StorageTrait::value_type const & some_value )
    {
        storage_[_StorageTrait::key_type( some_key )] = some_value;
    }
};

// #############################################################################################################################################

//! A template class
template
<
    class __Key,
    class __Value
>
class TemplateClass
{
//! Type for our storage
    /*!
     * Note that this results in a map from int to std::string
     */
    typedef traits::some_trait<__Key, class __Value> _StorageTrait;
    typedef _StorageTrait::type _Storage;

protected:
    //! Storage member variable to hold our data
    _Storage storage_;

public:
    // =========================================================================================================================================
    //! Default constructor
    TemplateClass()
    {
        //
    }

    // =========================================================================================================================================
    //! Copy constructor
    TemplateClass( TemplateClass const & other )
    :
        storage_( other.storage_ )
    {
        //
    }

    // =========================================================================================================================================
    //! If the given key is derived from our key type, cast construct our key type from it and continue as usual
    template
    <
        class __SomeType,
        typename std::enable_if<std::is_base_of<_StorageTrait::key_type, __SomeType>::value, int>::type = 0
    >
    void doSomething( __SomeType const & some_key, _StorageTrait::value_type const & some_value )
    {
        storage_[_StorageTrait::key_type( some_key )] = some_value;
    }
};
