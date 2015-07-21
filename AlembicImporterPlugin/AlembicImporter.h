#ifndef AlembicImporter_h
#define AlembicImporter_h

//// options
//#define aiWithTBB

#include "pch.h"



#ifdef _WIN32
typedef void (__stdcall *aiNodeEnumerator)(aiObject *node, void *userData);
#else
typedef void (*aiNodeEnumerator)(aiObject *node, void *userData);
#endif

struct aiV2 { float v[2]; };
struct aiV3 { float v[3]; };
struct aiM44 { float v[4][4]; };


struct aiSplitedMeshInfo
{
    int numFaces;
    int numIndices;
    int numVertices;
    int beginFace;
    int beginIndex;
    int triangulatedIndexCount;
};

struct aiSubmeshInfo
{
    int index;
    int splitIndex;
    int splitSubmeshIndex;
    int triangleCount;
    int facesetIndex;
};

struct aiFacesets
{
    int count;
    int *faceCounts;
    int *faceIndices;
};

aiCLinkage aiExport void            aiEnableFileLog(bool on, const char *path);

aiCLinkage aiExport aiContext*      aiCreateContext();
aiCLinkage aiExport void            aiDestroyContext(aiContext* ctx);

aiCLinkage aiExport bool            aiLoad(aiContext* ctx, const char *path);
aiCLinkage aiExport float           aiGetStartTime(aiContext* ctx);
aiCLinkage aiExport float           aiGetEndTime(aiContext* ctx);
aiCLinkage aiExport aiObject*       aiGetTopObject(aiContext* ctx);

aiCLinkage aiExport void            aiEnumerateChild(aiObject *obj, aiNodeEnumerator e, void *userData);
aiCLinkage aiExport const char*     aiGetNameS(aiObject* obj);
aiCLinkage aiExport const char*     aiGetFullNameS(aiObject* obj);
aiCLinkage aiExport uint32_t        aiGetNumChildren(aiObject* obj);
aiCLinkage aiExport void            aiSetCurrentTime(aiObject* obj, float time);

aiCLinkage aiExport void            aiEnableTriangulate(aiObject* obj, bool v);

aiCLinkage aiExport void            aiSwapHandedness(aiObject* obj, bool v);
aiCLinkage aiExport bool            aiIsHandednessSwapped(aiObject* obj);

aiCLinkage aiExport void            aiSwapFaceWinding(aiObject* obj, bool v);
aiCLinkage aiExport bool            aiIsFaceWindingSwapped(aiObject* obj);

aiCLinkage aiExport void            aiSetNormalMode(aiObject* obj, int m);
aiCLinkage aiExport int             aiGetNormalMode(aiObject* obj);

aiCLinkage aiExport void            aiEnableTangents(aiObject* obj, bool v);
aiCLinkage aiExport bool            aiAreTangentsEnabled(aiObject*);

aiCLinkage aiExport bool            aiHasXForm(aiObject* obj);
aiCLinkage aiExport bool            aiXFormGetInherits(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetPosition(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetAxis(aiObject* obj);
aiCLinkage aiExport float           aiXFormGetAngle(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetRotation(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetScale(aiObject* obj);
aiCLinkage aiExport aiM44           aiXFormGetMatrix(aiObject* obj);

aiCLinkage aiExport bool            aiHasPolyMesh(aiObject* obj);
aiCLinkage aiExport int             aiPolyMeshGetTopologyVariance(aiObject* obj);
aiCLinkage aiExport bool            aiPolyMeshHasNormals(aiObject* obj);
aiCLinkage aiExport bool            aiPolyMeshHasUVs(aiObject* obj);
aiCLinkage aiExport uint32_t        aiPolyMeshGetIndexCount(aiObject* obj);
aiCLinkage aiExport uint32_t        aiPolyMeshGetVertexCount(aiObject* obj);
aiCLinkage aiExport void            aiPolyMeshCopyIndices(aiObject* obj, int *dst);
aiCLinkage aiExport void            aiPolyMeshCopyVertices(aiObject* obj, abcV3 *dst);
aiCLinkage aiExport void            aiPolyMeshCopyNormals(aiObject* obj, abcV3 *dst);
aiCLinkage aiExport void            aiPolyMeshCopyUVs(aiObject* obj, abcV2 *dst);
aiCLinkage aiExport bool            aiPolyMeshGetSplitedMeshInfo(aiObject* obj, aiSplitedMeshInfo *smi, const aiSplitedMeshInfo *prev, int maxVertices);
aiCLinkage aiExport void            aiPolyMeshCopySplitedIndices(aiObject* obj, int *dst, const aiSplitedMeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshCopySplitedVertices(aiObject* obj, abcV3 *dst, const aiSplitedMeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshCopySplitedNormals(aiObject* obj, abcV3 *dst, const aiSplitedMeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshCopySplitedUVs(aiObject* obj, abcV2 *dst, const aiSplitedMeshInfo *smi);

aiCLinkage aiExport uint32_t        aiPolyMeshGetSplitCount(aiObject *obj, bool force_refresh);
aiCLinkage aiExport uint32_t        aiPolyMeshGetVertexBufferLength(aiObject* obj, uint32_t splitIndex);
aiCLinkage aiExport void            aiPolyMeshFillVertexBuffer(aiObject* obj, uint32_t splitIndex, abcV3 *positions, abcV3 *normals, abcV2 *uvs, abcV4 *tangents);
aiCLinkage aiExport uint32_t        aiPolyMeshPrepareSubmeshes(aiObject* obj, const aiFacesets* facesets);
aiCLinkage aiExport uint32_t        aiPolyMeshGetSplitSubmeshCount(aiObject* obj, uint32_t splitIndex);
aiCLinkage aiExport bool            aiPolyMeshGetNextSubmesh(aiObject* obj, aiSubmeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshFillSubmeshIndices(aiObject* obj, int *dst, const aiSubmeshInfo *smi);

struct aiTextureMeshData
{
    int numIndices;
    bool isNormalIndexed;
    bool isUvIndexed;
    void *texIndices;
    void *texVertices;
    void *texNormals;
    void *texUvs;
};
aiCLinkage aiExport void            aiPolyMeshCopyDataToTexture(aiObject* obj, aiTextureMeshData *dst);


aiCLinkage aiExport bool            aiHasCurves(aiObject* obj);

aiCLinkage aiExport bool            aiHasPoints(aiObject* obj);

aiCLinkage aiExport bool            aiHasCamera(aiObject* obj);
aiCLinkage aiExport void            aiCameraGetParams(aiObject* obj, aiCameraParams *params);

aiCLinkage aiExport bool            aiHasLight(aiObject* obj);

aiCLinkage aiExport bool            aiHasMaterial(aiObject* obj);

#endif // AlembicImporter_h
