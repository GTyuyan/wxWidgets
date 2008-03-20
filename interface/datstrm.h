/////////////////////////////////////////////////////////////////////////////
// Name:        datstrm.h
// Purpose:     interface of wxDataOutputStream
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxDataOutputStream
    @wxheader{datstrm.h}

    This class provides functions that write binary data types in a
    portable way. Data can be written in either big-endian or little-endian
    format, little-endian being the default on all architectures.

    If you want to write data to text files (or streams) use
    wxTextOutputStream instead.

    The  operator is overloaded and you can use this class like a standard
    C++ iostream. See wxDataInputStream for its
    usage and caveats.

    See also wxDataInputStream.

    @library{wxbase}
    @category{streams}
*/
class wxDataOutputStream
{
public:
    //@{
    /**
        )
        Constructs a datastream object from an output stream. Only write methods will
        be available. The second form is only available in Unicode build of wxWidgets.

        @param stream
            The output stream.
        @param conv
            Charset conversion object object used to encoding Unicode
            strings before writing them to the stream
            in Unicode mode (see WriteString()
            documentation for detailed description). Note that you must not destroy
            conv before you destroy this wxDataOutputStream instance! It is
            recommended to use default value (UTF-8).
    */
    wxDataOutputStream(wxOutputStream& stream);
    wxDataOutputStream(wxOutputStream& stream);
    //@}

    /**
        Destroys the wxDataOutputStream object.
    */
    ~wxDataOutputStream();

    /**
        If @a be_order is @true, all data will be written in big-endian
        order, e.g. for reading on a Sparc or from Java-Streams (which
        always use big-endian order), otherwise data will be written in
        little-endian order.
    */
    void BigEndianOrdered(bool be_order);

    //@{
    /**
        Writes an array of 16 bit unsigned integer to the stream. The amount of
        16 bit unsigned integer to write is specified with the @a size variable.
    */
    void Write16(wxUint16 i16);
    void Write16(const wxUint16* buffer, size_t size);
    //@}

    //@{
    /**
        Writes an array of 32 bit unsigned integer to the stream. The amount of
        32 bit unsigned integer to write is specified with the @a size variable.
    */
    void Write32(wxUint32 i32);
    void Write32(const wxUint32* buffer, size_t size);
    //@}

    //@{
    /**
        Writes an array of 64 bit unsigned integer to the stream. The amount of
        64 bit unsigned integer to write is specified with the @a size variable.
    */
    void Write64(wxUint64 i64);
    void Write64(const wxUint64* buffer, size_t size);
    //@}

    //@{
    /**
        Writes an array of bytes to the stream. The amount of bytes to write is
        specified with the @a size variable.
    */
    void Write8(wxUint8 i8);
    void Write8(const wxUint8* buffer, size_t size);
    //@}

    //@{
    /**
        Writes an array of double to the stream. The amount of double to write is
        specified with the @a size variable.
    */
    void WriteDouble(double f);
    void WriteDouble(const double* buffer, size_t size);
    //@}

    /**
        Writes @a string to the stream. Actually, this method writes the size of
        the string before writing @a string itself.
        In ANSI build of wxWidgets, the string is written to the stream in exactly
        same way it is represented in memory. In Unicode build, however, the string
        is first converted to multibyte representation with @e conv object passed
        to stream's constructor (consequently, ANSI application can read data
        written by Unicode application, as long as they agree on encoding) and this
        representation is written to the stream. UTF-8 is used by default.
    */
    void WriteString(const wxString& string);
};



/**
    @class wxDataInputStream
    @wxheader{datstrm.h}

    This class provides functions that read binary data types in a
    portable way. Data can be read in either big-endian or little-endian
    format, little-endian being the default on all architectures.

    If you want to read data from text files (or streams) use
    wxTextInputStream instead.

    The  operator is overloaded and you can use this class like a standard C++
    iostream.
    Note, however, that the arguments are the fixed size types wxUint32, wxInt32 etc
    and on a typical 32-bit computer, none of these match to the "long" type
    (wxInt32
    is defined as signed int on 32-bit architectures) so that you cannot use long.
    To avoid
    problems (here and elsewhere), make use of the wxInt32, wxUint32, etc types.

    For example:

    @code
    wxFileInputStream input( "mytext.dat" );
      wxDataInputStream store( input );
      wxUint8 i1;
      float f2;
      wxString line;

      store  i1;       // read a 8 bit integer.
      store  i1  f2; // read a 8 bit integer followed by float.
      store  line;     // read a text line
    @endcode

    See also wxDataOutputStream.

    @library{wxbase}
    @category{streams}
*/
class wxDataInputStream
{
public:
    //@{
    /**
        )
        Constructs a datastream object from an input stream. Only read methods will
        be available. The second form is only available in Unicode build of wxWidgets.

        @param stream
            The input stream.
        @param conv
            Charset conversion object object used to decode strings in Unicode
            mode (see ReadString()
            documentation for detailed description). Note that you must not destroy
            conv before you destroy this wxDataInputStream instance!
    */
    wxDataInputStream(wxInputStream& stream);
    wxDataInputStream(wxInputStream& stream);
    //@}

    /**
        Destroys the wxDataInputStream object.
    */
    ~wxDataInputStream();

    /**
        If @a be_order is @true, all data will be read in big-endian
        order, such as written by programs on a big endian architecture
        (e.g. Sparc) or written by Java-Streams (which always use
        big-endian order).
    */
    void BigEndianOrdered(bool be_order);

    //@{
    /**
        Reads 16 bit unsigned integers from the stream in a specified buffer. the
        amount of 16 bit unsigned integer to read is specified by the @a size variable.
    */
    wxUint16 Read16();
    void Read16(wxUint16* buffer, size_t size);
    //@}

    //@{
    /**
        Reads 32 bit unsigned integers from the stream in a specified buffer. the
        amount of
        32 bit unsigned integer to read is specified by the @a size variable.
    */
    wxUint32 Read32();
    void Read32(wxUint32* buffer, size_t size);
    //@}

    //@{
    /**
        Reads 64 bit unsigned integers from the stream in a specified buffer. the
        amount of
        64 bit unsigned integer to read is specified by the @a size variable.
    */
    wxUint64 Read64();
    void Read64(wxUint64* buffer, size_t size);
    //@}

    //@{
    /**
        Reads bytes from the stream in a specified buffer. The amount of
        bytes to read is specified by the @a size variable.
    */
    wxUint8 Read8();
    void Read8(wxUint8* buffer, size_t size);
    //@}

    //@{
    /**
        Reads double data (IEEE encoded) from the stream in a specified buffer. the
        amount of
        double to read is specified by the @a size variable.
    */
    double ReadDouble();
    void ReadDouble(double* buffer, size_t size);
    //@}

    /**
        Reads a string from a stream. Actually, this function first reads a long
        integer specifying the length of the string (without the last null character)
        and then reads the string.
        In Unicode build of wxWidgets, the fuction first reads multibyte (char*)
        string from the stream and then converts it to Unicode using the @e conv
        object passed to constructor and returns the result as wxString. You are
        responsible for using the same convertor as when writing the stream.
        See also wxDataOutputStream::WriteString.
    */
    wxString ReadString();
};

