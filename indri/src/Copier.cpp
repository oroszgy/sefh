// 
// Warning: This file is automatically generated
// 

#include "indri/Copier.hpp"
#include "indri/QuerySpec.hpp"

namespace indri { 
  namespace lang { 
    Copier::~Copier() {}

    void Copier::defaultBefore( class Node* oldNode ) {}
    Node* Copier::defaultAfter( class Node* oldNode, class Node* newNode ) { return newNode; }

    void Copier::before( class IndexTerm* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class IndexTerm* oldNode, class IndexTerm* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class Field* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class Field* oldNode, class Field* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentInside* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentInside* oldNode, class ExtentInside* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class WeightedExtentOr* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class WeightedExtentOr* oldNode, class WeightedExtentOr* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentOr* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentOr* oldNode, class ExtentOr* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentAnd* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentAnd* oldNode, class ExtentAnd* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class BAndNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class BAndNode* oldNode, class BAndNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class UWNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class UWNode* oldNode, class UWNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ODNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ODNode* oldNode, class ODNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FilReqNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FilReqNode* oldNode, class FilReqNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FilRejNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FilRejNode* oldNode, class FilRejNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FieldLessNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FieldLessNode* oldNode, class FieldLessNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FieldGreaterNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FieldGreaterNode* oldNode, class FieldGreaterNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FieldBetweenNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FieldBetweenNode* oldNode, class FieldBetweenNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FieldEqualsNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FieldEqualsNode* oldNode, class FieldEqualsNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class RawScorerNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class RawScorerNode* oldNode, class RawScorerNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class TermFrequencyScorerNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class TermFrequencyScorerNode* oldNode, class TermFrequencyScorerNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class CachedFrequencyScorerNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class CachedFrequencyScorerNode* oldNode, class CachedFrequencyScorerNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class PriorNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class PriorNode* oldNode, class PriorNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class OrNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class OrNode* oldNode, class OrNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class NotNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class NotNode* oldNode, class NotNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class MaxNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class MaxNode* oldNode, class MaxNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class CombineNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class CombineNode* oldNode, class CombineNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class WAndNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class WAndNode* oldNode, class WAndNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class WSumNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class WSumNode* oldNode, class WSumNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class WeightNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class WeightNode* oldNode, class WeightNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentRestriction* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentRestriction* oldNode, class ExtentRestriction* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FixedPassage* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FixedPassage* oldNode, class FixedPassage* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FilterNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FilterNode* oldNode, class FilterNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ListAccumulator* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ListAccumulator* oldNode, class ListAccumulator* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ContextCounterNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ContextCounterNode* oldNode, class ContextCounterNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ContextSimpleCounterNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ContextSimpleCounterNode* oldNode, class ContextSimpleCounterNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ScoreAccumulatorNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ScoreAccumulatorNode* oldNode, class ScoreAccumulatorNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class AnnotatorNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class AnnotatorNode* oldNode, class AnnotatorNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class FieldWildcard* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class FieldWildcard* oldNode, class FieldWildcard* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class NestedExtentInside* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class NestedExtentInside* oldNode, class NestedExtentInside* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class NestedRawScorerNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class NestedRawScorerNode* oldNode, class NestedRawScorerNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentEnforcement* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentEnforcement* oldNode, class ExtentEnforcement* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ContextInclusionNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ContextInclusionNode* oldNode, class ContextInclusionNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class LengthPrior* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class LengthPrior* oldNode, class LengthPrior* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class DocumentStructureNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class DocumentStructureNode* oldNode, class DocumentStructureNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ShrinkageScorerNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ShrinkageScorerNode* oldNode, class ShrinkageScorerNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentDescendant* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentDescendant* oldNode, class ExtentDescendant* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentChild* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentChild* oldNode, class ExtentChild* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class ExtentParent* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class ExtentParent* oldNode, class ExtentParent* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class WildcardTerm* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class WildcardTerm* oldNode, class WildcardTerm* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class PlusNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class PlusNode* oldNode, class PlusNode* newNode ) { return defaultAfter( oldNode, newNode ); }
    void Copier::before( class WPlusNode* oldNode ) { defaultBefore( oldNode ); }
    Node* Copier::after( class WPlusNode* oldNode, class WPlusNode* newNode ) { return defaultAfter( oldNode, newNode ); }
 }
}

