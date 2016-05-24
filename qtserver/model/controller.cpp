/**
 * @file
 * The command handling controller code.
 *
 * 
 */


#include "controller.h"
#include <stdarg.h>

#define REG(xx,cc,yy) regCommand(xx,cc,&Controller::method##yy)
#define METHOD(xx) void Controller::method##xx (int argc,char *argv[])

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

Controller::Controller(PatchLibrary *l,Server *s){
    commandct=0;
    server=s;
    library=l;
    
    
    REG("test",0,Test);
    REG("startprims",0,StartPrims);
    REG("nextprim",0,NextPrim);
    
    REG("startcomps",0,StartComps);
    REG("nextcomp",0,NextComp);
    REG("compinnm",1,CompInName);
    REG("compoutnm",1,CompOutName);
    
    REG("compparam",1,CompParam); // paramidx
    REG("compenum",2,CompEnum); // paramidx enumidx
    
    REG("die",0,Die);
    
    REG("clear",0,Clear);
    REG("np",1,NewPatch); // patchid
    REG("dp",1,DelPatch); // patchid
    REG("sra",4,SetRunAlways); // patchid componentid outputidx y/n
    REG("nc",3,NewComponent); // patchid componentid type
    REG("dc",2,DeleteComponent); // patchid componentid
    REG("lc",5,LinkComponent); // patchid incomponentid input outcomponentid output
    REG("ui",3,UnlinkComponentInput); // patchid componentid input
    REG("uo",3,UnlinkComponentOutput); // patchid componentid output
    REG("p",5,ParamSet); // patchid componentid paramid code encval
    REG("run",1,RunPatch); // patchid
}


void Controller::output(const char *s,...){
    char buf[256];
        
    va_list args;
    va_start(args,s);
        
    vsprintf(buf,s,args);
    
    if(server){
        server->output(buf);
    } else {
        printf("OUTPUT> %s\n",buf);
    }
}



METHOD(Test) {
    printf("test does nothing\n");
    server->success();
}
METHOD(Die) {
    server->success();
    server->die();
}

extern void firstPrim();
extern const char *nextPrim();

METHOD(StartPrims) {
    printf("Sending prims\n");
    firstPrim();
    const char *s = nextPrim();
    printf("Prim: %s\n",s);
    server->sendPrim(s);
}

METHOD(NextPrim) {
    if(const char *s = nextPrim()){
        printf("Prim: %s\n",s);
        server->sendPrim(s);
    } else
        server->sendPrimsDone();
}


// arguments : patchid
METHOD(NewPatch){
    uint32_t id = atoi(argv[0]);
    
    if(library->get(id)){
        server->fail(SE_ALREADY);
    } else {
        library->create(id);
        server->success(id);
    }
}

METHOD(DelPatch){
    uint32_t id = atoi(argv[0]);
    Patch *p;
    if(p=library->get(id)){
        library->del(id); // will destruct the patch
        server->success();
    } else {
        server->fail(SE_NOSUCHPATCH);
    }
}

METHOD(Clear){
    library->clear();
    server->success();
}

METHOD(SetRunAlways){
    uint32_t pid = atoi(argv[0]);
    Patch *p = library->get(pid);
    if(!p)throw SE_NOSUCHPATCH;
    uint32_t cid = atoi(argv[1]);
    Component *c = p->getComponent(cid);
    if(!c)throw SE_NOSUCHCOMP;
    uint32_t oid = atoi(argv[2]);
    if(oid>=ComponentType::NUMOUTPUTS)throw SE_OUTPUTRANGE;
    if(c->type->outputTypes[oid]==T_INVALID)
        throw SE_OUTPUTRANGE;
    c->setOutputRunAlways(oid,*argv[3]=='y');
    server->success();
}
    
    
    
METHOD(NewComponent){
    uint32_t pid = atoi(argv[0]);
    Patch *p = library->get(pid);
    if(!p)throw SE_NOSUCHPATCH;
    
    uint32_t cid = atoi(argv[1]);
    
    const char *type = argv[2];
    p->createComponent(cid,type);
    server->success(cid);
}

METHOD(DeleteComponent){
    uint32_t pid = atoi(argv[0]);
    uint32_t cid = atoi(argv[1]);
    
    Patch *p = library->get(pid);
    p->dump();
    if(!p)throw SE_NOSUCHPATCH;
    
    p->deleteComponent(cid);
    server->success(cid);
}

static ComponentType *curCT = NULL;
inline char getconntypestr(ConnectionType t){
    switch(t){
    case T_FLOW:return 'f';
    case T_FLOAT:return 'n';
    default:
    case T_INVALID:return 'i';
    }
}
    
void Controller::sendCurCT(){
    char buf[1024];
    
    if(!curCT)
        output("411 comps done");
    else {
        // first line - name and ins/outs
        sprintf(buf,"410 %s:",curCT->name);
        int n = strlen(buf);
        for(int i=0;i<ComponentType::NUMINPUTS;i++){
            buf[n++] = getconntypestr(curCT->inputTypes[i]);
        }
        buf[n++]=':';
        for(int i=0;i<ComponentType::NUMOUTPUTS;i++){
            buf[n++] = getconntypestr(curCT->outputTypes[i]);
        }
        buf[n]=0;
        
        
        // output the param count etc.
        sprintf(buf+strlen(buf),":%d:%s:%d:%d",
                curCT->paramct,curCT->category,curCT->width,curCT->height);
        output(buf);
    
    }
}

METHOD(CompInName){
    char buf[1024];
    int idx = atoi(argv[0]);
    if(idx>=ComponentType::NUMINPUTS)
        throw SE_INPUTRANGE;
    sprintf(buf,"414 %s",curCT->inputNames[idx]);
    output(buf);
}

METHOD(CompOutName){
    char buf[1024];
    int idx = atoi(argv[0]);
    if(idx>=ComponentType::NUMINPUTS)
        throw SE_INPUTRANGE;
    sprintf(buf,"415 %s",curCT->outputNames[idx]);
    output(buf);
}


METHOD(CompParam){
    char buf[1024];
    int pidx = atoi(argv[0]);
    if(pidx>=curCT->paramct)
        throw SE_NOSUCHPARAM;
    sprintf(buf,"412 %s",curCT->params[pidx]->getDesc());
    output(buf);
}

METHOD(CompEnum){
    char buf[1024];
    int pidx = atoi(argv[0]);
    if(pidx>=curCT->paramct)
        throw SE_NOSUCHPARAM;
    if(curCT->params[pidx]->code != 'e')
        throw SE_BADPARAMTYPE;
    
    EnumParameter *ep = (EnumParameter *)(curCT->params[pidx]);
    int eidx = atoi(argv[1]);
    if(eidx >= ep->getCount())
        throw SE_ENUMOUTOFRANGE;
    
    sprintf(buf,"413 %s",ep->getString(eidx));
    output(buf);
}

METHOD(StartComps){
    curCT = ComponentType::types->head();
    sendCurCT();
}

METHOD(NextComp){
    if(curCT)
        curCT = ComponentType::types->next(curCT);
    sendCurCT();
}


    

METHOD(LinkComponent){
    uint32_t pid = atoi(argv[0]);
    uint32_t inid = atoi(argv[1]);
    uint32_t input = atoi(argv[2]);
    uint32_t outid = atoi(argv[3]);
    uint32_t output = atoi(argv[4]);
    
    Patch *p = library->get(pid);
    if(!p)throw SE_NOSUCHPATCH;
    
    Component *in = p->getComponent(inid);
    if(!in)throw SE_NOSUCHCOMP;
    
    Component *out = p->getComponent(outid);
    if(!out)throw SE_NOSUCHCOMP;
    
    in->linkInput(input,out,output);
    server->success();
}

METHOD(UnlinkComponentInput){
    uint32_t pid = atoi(argv[0]);
    uint32_t cid = atoi(argv[1]);
    uint32_t input = atoi(argv[2]);
    
    Patch *p = library->get(pid);
    if(!p)throw SE_NOSUCHPATCH;
    
    Component *c = p->getComponent(cid);
    if(!c)throw SE_NOSUCHCOMP;
    
    c->unlinkInput(input);
    server->success();
}

METHOD(UnlinkComponentOutput){
    uint32_t pid = atoi(argv[0]);
    uint32_t cid = atoi(argv[1]);
    uint32_t output = atoi(argv[2]);
    
    Patch *p = library->get(pid);
    if(!p)throw SE_NOSUCHPATCH;
    
    Component *c = p->getComponent(cid);
    if(!c)throw SE_NOSUCHCOMP;
    
    p->unlinkComponentOutput(c,output);
    server->success();
}

METHOD(ParamSet){
    uint32_t pid = atoi(argv[0]);
    uint32_t cid = atoi(argv[1]);
    int paramid = atoi(argv[2]);
    char code = argv[3][0];
    char *val = argv[4];
    
    Patch *p = library->get(pid);
    if(!p)throw SE_NOSUCHPATCH;
    
    Component *c = p->getComponent(cid);
    if(!c)throw SE_NOSUCHCOMP;
    
    printf("Setting parameter %d in component %s to %s\n",
           paramid,c->type->name,val);
    
    c->setParamValue(paramid,code,val);
    server->success();
}
    

METHOD(RunPatch){
    uint32_t pid = atoi(argv[0]);
    library->instantiateAsActive(pid);
    server->success();
}
#pragma GCC diagnostic pop
