/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.36
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package lemurproject.indri;
import java.util.Map;
public class IndexEnvironment {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected IndexEnvironment(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IndexEnvironment obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      indriJNI.delete_IndexEnvironment(swigCPtr);
    }
    swigCPtr = 0;
  }

  public IndexEnvironment() {
    this(indriJNI.new_IndexEnvironment(), true);
  }

  
/**
       Set the document root path
       @param documentRoot path to document root.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setDocumentRoot(String documentRoot) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setDocumentRoot(swigCPtr, this, documentRoot);
  }

  
/**
 Set anchor text root path.
@param anchorTextRoot path to anchor text root.
@throws Exception if 
*/
public void setAnchorTextPath(String anchorTextRoot) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setAnchorTextPath(swigCPtr, this, anchorTextRoot);
  }

  
/**
      Set offset metadata root path.
      @param offsetMetadataRoot path to offset metadata root.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setOffsetMetadataPath(String offsetMetadataRoot) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setOffsetMetadataPath(swigCPtr, this, offsetMetadataRoot);
  }

  
/**
       Set offset annotations root path.
       @param offsetAnnotationsRoot path to offset annotations root.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setOffsetAnnotationsPath(String offsetAnnotationsRoot) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setOffsetAnnotationsPath(swigCPtr, this, offsetAnnotationsRoot);
  }

  
/**
       Add parsing information for a file class. Data for these parameters
       is passed into the FileClassEnvironmentFactory
       @param name name of this file class, eg trecweb
       @param iterator document iterator for this file class
       @param parser document parser for this file class
       @param tokenizer document tokenizer for this file class
       @param startDocTag tag indicating start of a document
       @param endDocTag tag indicating the end of a document
       @param endMetadataTag tag indicating the end of the metadata fields
       @param include default tags whose contents should be included in the index
       @param exclude tags whose contents should be excluded from the index
       @param index tags that should be forwarded to the index for tag extents
       @param metadata tags whose contents should be indexed as metadata
       @param conflations tags that should be conflated

@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void addFileClass(String name, String iterator, String parser, String tokenizer, String startDocTag, String endDocTag, String endMetadataTag, String[] include, String[] exclude, String[] index, String[] metadata, Map conflations) throws java.lang.Exception {
    indriJNI.IndexEnvironment_addFileClass__SWIG_0(swigCPtr, this, name, iterator, parser, tokenizer, startDocTag, endDocTag, endMetadataTag, include, exclude, index, metadata, conflations);
  }

  
/**
       Get a named file class.
       @param name The name of the file class to retrieve.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public Specification getFileClassSpec(String name) throws java.lang.Exception {
  return indriJNI.IndexEnvironment_getFileClassSpec(swigCPtr, this, name);
}

  
/**
       Add a file class.
       @param spec The file class to add.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void addFileClass(Specification spec) throws java.lang.Exception {
    indriJNI.IndexEnvironment_addFileClass__SWIG_1(swigCPtr, this, spec);
  }

  
/**
       Delete an existing document.
       @param documentID The document to delete.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void deleteDocument(int documentID) throws java.lang.Exception {
    indriJNI.IndexEnvironment_deleteDocument(swigCPtr, this, documentID);
  }

  
/**
       Set names of fields to be indexed.  This call indicates to the index that information about
       these fields should be stored in the index so they can be used in queries.  This does not
       affect whether or not the text in a particular field is stored in an index.
       @param fieldNames the list of fields.

@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setIndexedFields(String[] fieldNames) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setIndexedFields(swigCPtr, this, fieldNames);
  }

  
/**
       Set the numeric property of a field. 
       @param fieldName the field.
       @param isNumeric true if the field is a numeric field, false if not.
       @param parserName The name of the Transformation to use to compute the numeric value of the field. Repository currently recognizes the name NumericFieldAnnotator.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setNumericField(String fieldName, boolean isNumeric, String parserName) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setNumericField__SWIG_0(swigCPtr, this, fieldName, isNumeric, parserName);
  }

  
/**
       Set the numeric property of a field. 
       @param fieldName the field.
       @param isNumeric true if the field is a numeric field, false if not.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setNumericField(String fieldName, boolean isNumeric) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setNumericField__SWIG_1(swigCPtr, this, fieldName, isNumeric);
  }

  
/**
       Set names of metadata fields to be indexed for fast retrieval.
       The forward fields are indexed in a B-Tree mapping (documentID, metadataValue).
       If a field is not forward indexed, the documentMetadata calls will still work, but they
       will be slower (the document has to be retrieved, decompressed and parsed to get the metadata back,
       instead of just a B-Tree lookup).  The backward indexed fields store a mapping of (metadataValue, documentID).
       If a field is not backward indexed, the documentIDsFromMetadata and documentFromMetadata calls will not work.
       @param forward the list of fields to forward index.
       @param backward the list of fields to backward index.

@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setMetadataIndexedFields(String[] forward, String[] backward) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setMetadataIndexedFields(swigCPtr, this, forward, backward);
  }

  
/**
       set the list of stopwords
       @param stopwords the list of stopwords
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setStopwords(String[] stopwords) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setStopwords(swigCPtr, this, stopwords);
  }

  
/**
       set the stemmer to use
       @param stemmer the stemmer to use. One of krovetz, porter

@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setStemmer(String stemmer) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setStemmer(swigCPtr, this, stemmer);
  }

  
/**
       set the amount of memory to use for internal structures
       @param memory the number of bytes to use.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setMemory(long memory) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setMemory(swigCPtr, this, memory);
  }

  
/**
       set normalization of case and some punctuation; default is true (normalize during indexing and at query time)
       @param normalize True, if text should be normalized, false otherwise.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void setNormalization(boolean normalize) throws java.lang.Exception {
    indriJNI.IndexEnvironment_setNormalization(swigCPtr, this, normalize);
  }

  
/**
       create a new index and repository
       @param repositoryPath the path to the repository
       @param callback IndexStatus object to be notified of indexing progress.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void create(String repositoryPath, IndexStatus callback) throws java.lang.Exception {
    indriJNI.IndexEnvironment_create__SWIG_0(swigCPtr, this, repositoryPath, IndexStatus.getCPtr(callback), callback);
  }

  
/**
       create a new index and repository
       @param repositoryPath the path to the repository
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void create(String repositoryPath) throws java.lang.Exception {
    indriJNI.IndexEnvironment_create__SWIG_1(swigCPtr, this, repositoryPath);
  }

  
/**
       open an existing index and repository
       @param repositoryPath the path to the repository
       @param callback IndexStatus object to be notified of indexing progress.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void open(String repositoryPath, IndexStatus callback) throws java.lang.Exception {
    indriJNI.IndexEnvironment_open__SWIG_0(swigCPtr, this, repositoryPath, IndexStatus.getCPtr(callback), callback);
  }

  
/**
       open an existing index and repository
       @param repositoryPath the path to the repository
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void open(String repositoryPath) throws java.lang.Exception {
    indriJNI.IndexEnvironment_open__SWIG_1(swigCPtr, this, repositoryPath);
  }

  
/**
       close the index and repository
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void close() throws java.lang.Exception {
    indriJNI.IndexEnvironment_close(swigCPtr, this);
  }

  
/**
       Add the text in a file to the index and repository.  The fileClass of this file
       will be chosen based on the file extension.  If the file has no extension, it will
       be skipped.  Information about indexing progress will be passed to the callback.
       @param fileName the file to add
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void addFile(String fileName) throws java.lang.Exception {
    indriJNI.IndexEnvironment_addFile__SWIG_0(swigCPtr, this, fileName);
  }

  
/**
       add a file of the specified file class to the index and repository
       @param fileName the file to add
       @param fileClass the file class to add (eg trecweb).
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public void addFile(String fileName, String fileClass) throws java.lang.Exception {
    indriJNI.IndexEnvironment_addFile__SWIG_1(swigCPtr, this, fileName, fileClass);
  }

  
/**

       Adds a string to the index and repository.  The documentString is assumed to contain the kind of
       text that would be found in a file of type fileClass.
       @param fileName the document to add
       @param fileClass the file class to add (eg trecweb).
       @param metadata the metadata pairs associated with the string.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public int addString(String fileName, String fileClass, Map metadata) throws java.lang.Exception {
    return indriJNI.IndexEnvironment_addString__SWIG_0(swigCPtr, this, fileName, fileClass, metadata);
  }

  
/**
       add an already parsed document to the index and repository
       @param documentString the document to add
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public int addString(String documentString, String fileClass, Map metadata, TagExtent[] tags) throws java.lang.Exception {
    return indriJNI.IndexEnvironment_addString__SWIG_1(swigCPtr, this, documentString, fileClass, metadata, tags);
  }

  
/**
       add an already parsed document to the index and repository
       @param document the document to add
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public int addParsedDocument(ParsedDocument document) throws java.lang.Exception {
    return indriJNI.IndexEnvironment_addParsedDocument(swigCPtr, this, document);
  }

  
/**
       Returns the number of documents indexed so far in this session.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public int documentsIndexed() throws java.lang.Exception {
    return indriJNI.IndexEnvironment_documentsIndexed(swigCPtr, this);
  }

  
/**

       Returns the number of documents considered for indexing,
       which is the sum of the documents indexed and the documents
       skipped.
@throws Exception if a lemur::api::Exception was thrown by the JNI library.
*/
public int documentsSeen() throws java.lang.Exception {
    return indriJNI.IndexEnvironment_documentsSeen(swigCPtr, this);
  }

}
