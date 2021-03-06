/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.36
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace Indri {

using System;
using System.Runtime.InteropServices;

public class QueryExpander : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal QueryExpander(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(QueryExpander obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~QueryExpander() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        indri_csharpPINVOKE.delete_QueryExpander(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
    }
  }

  public ScoredExtentResultVector runExpandedQuery(string originalQuery, int resultsRequested, bool verbose) {
    ScoredExtentResultVector ret = new ScoredExtentResultVector(indri_csharpPINVOKE.QueryExpander_runExpandedQuery__SWIG_0(swigCPtr, originalQuery, resultsRequested, verbose), true);
    if (indri_csharpPINVOKE.SWIGPendingException.Pending) throw indri_csharpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public ScoredExtentResultVector runExpandedQuery(string originalQuery, int resultsRequested) {
    ScoredExtentResultVector ret = new ScoredExtentResultVector(indri_csharpPINVOKE.QueryExpander_runExpandedQuery__SWIG_1(swigCPtr, originalQuery, resultsRequested), true);
    if (indri_csharpPINVOKE.SWIGPendingException.Pending) throw indri_csharpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual string expand(string originalQuery, ScoredExtentResultVector results) {
    string ret = indri_csharpPINVOKE.QueryExpander_expand(swigCPtr, originalQuery, ScoredExtentResultVector.getCPtr(results));
    if (indri_csharpPINVOKE.SWIGPendingException.Pending) throw indri_csharpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
