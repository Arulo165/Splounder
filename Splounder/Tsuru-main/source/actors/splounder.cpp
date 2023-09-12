#include "game/actor/stage/enemy.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/graphics/model/modelnw.h"
#include "tsuru/utils.h"
#include "math/functions.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/rectcollider.h"
#include "log.h"

class  Splounder : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Splounder, Enemy);

public:
    Splounder(const ActorBuildInfo* buildInfo);
    virtual ~Splounder() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void beginChase();
    void endChase();

    static const HitboxCollider::Info collisionInfo;
    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    RectCollider rectCollider;
    ModelWrapper* model;
    bool chasing;

    StageActor* target;
    f32 targetInitialY;
    f32 launchHeight;

    DECLARE_STATE(Splounder, Walk);
    DECLARE_STATE(Splounder, Turn);
    DECLARE_STATE(Splounder, Launch);
};

CREATE_STATE(Splounder, Walk);
CREATE_STATE(Splounder, Turn);
CREATE_STATE(Splounder, Launch);

const ActorInfo SplounderActorInfo = {
    Vec2i(8, -8), Vec2i(8, -8), Vec2i(32, 32), 0, 0, 0, 0, 0
};

REGISTER_PROFILE(Splounder, ProfileID::Splounder, "Splounder", &SplounderActorInfo, Profile::Flags::DontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::Splounder, Profile::LoadResourcesAt::Course, "splounder");

Splounder::Splounder(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , chasing(false)
    , target(nullptr)
    , targetInitialY(0.0f)
    , launchHeight(128.0f)
{ }

const HitboxCollider::Info Splounder::collisionInfo = {
    Vec2f(0.0f, 15.0f), Vec2f(27.0f, 33.0f), HitboxCollider::Shape::Rectangle, 3, 0, 0xFFFFFFFF, 0xFFFBFFFF, 0, &Splounder::collisionCallback
};

u32 Splounder::onCreate() {
    this->model = ModelWrapper::create("splounder", "splounder", 3);
    this->scale.x = 0.1f;
    this->scale.y = 0.1f;
    this->scale.z = 0.1f;
    this->model->playSklAnim("walk", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);

    PhysicsMgr::Sensor belowSensor = { -6,  6,  0 };
    PhysicsMgr::Sensor aboveSensor = { -6,  6, 28 };
    PhysicsMgr::Sensor sidesSensor = {  8, 24, 12 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sidesSensor);

    this->direction = this->directionToPlayerH(this->position);
    this->rotation.y = Direction::directionToRotationList[this->direction];

    this->hitboxCollider.init(this, &Splounder::collisionInfo, nullptr);
    this->addHitboxColliders();

    PolygonCollider::Info colliderInfo = {
        Vec2f(0.0f, 14.0f), 0.0f, 0.0f, Vec2f(-5.5f, 10.0f), Vec2f(5.5f, -12.0f), 0
    };

    this->rectCollider.init(this, colliderInfo);
    this->rectCollider.setType(ColliderBase::Type::Bouncy);
    //ColliderMgr::instance()->add(&rectCollider);

    this->doStateChange(&Splounder::StateID_Walk);

    return this->onExecute();
}

u32 Splounder::onExecute() {
    if (this->target != nullptr) {
        if (this->target->position.y > this->targetInitialY + this->launchHeight) {
            this->target->speed.y *= 0.0f;
            this->target = nullptr;
        }
    }

    this->states.execute();

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position + Vec3f(0.0f, 20.0f, 0.0f));
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();

    this->offscreenDelete(0);
    this->rectCollider.execute();

    return 1;
}

u32 Splounder::onDraw() {
    this->model->draw();

    return 1;
}

void Splounder::beginChase() {
    this->chasing    = true;
    this->speed.x    = this->direction == Direction::Left ? -0.0f : 0.0f;
    this->maxSpeed.x = this->direction == Direction::Left ? -0.0f : 0.0f;
    this->model->sklAnims[0]->frameCtrl.speed = 0.0f;
}

void Splounder::endChase() {
    this->chasing    = false;
    this->speed.x    = this->direction == Direction::Left ? -0.0f : 0.0f;
    this->maxSpeed.x = this->direction == Direction::Left ? -0.0f : 0.0f;
    this->model->sklAnims[0]->frameCtrl.speed = 0.0f;
}

/** STATE: Walk */

void Splounder::beginState_Walk() {
    f32 speed = this->chasing ? 0.0f : 0.0f;
    this->speed.x    = this->direction == Direction::Left ? -speed : speed;
    this->maxSpeed.x = this->direction == Direction::Left ? -speed : speed;
}

void Splounder::executeState_Walk() {
    
   
    if (this->physicsMgr.isOnGround()) {
        this->speed.y = 0.0f;
    }

    Vec2f distToPlayer;
    if (this->distanceToPlayer(distToPlayer) > -1 && sead::Mathf::abs(distToPlayer.x) < 8.0f * 16.0f && sead::Mathf::abs(distToPlayer.y) < 6.0f * 16.0f) {
        if ((this->direction == Direction::Left && distToPlayer.x < 0) || (this->direction == Direction::Right && distToPlayer.x > 0)) {
            this->beginChase();
        }

        if (this->chasing) {
            if ((this->direction == Direction::Left && distToPlayer.x > 0) || (this->direction == Direction::Right && distToPlayer.x < 0)) {
                this->doStateChange(&Splounder::StateID_Turn);
            }
        }
    } else {
        this->endChase();
    }

    if (this->physicsMgr.isOnGround()) {
        this->speed.y = 0.0f;
    }

    if (this->physicsMgr.isCollided(this->direction) && !this->chasing) {
        this->doStateChange(&Splounder::StateID_Turn);
    }
}

void Splounder::endState_Walk() { }

/** STATE: Turn */

void Splounder::beginState_Turn() {
    this->direction ^= 1;
    this->speed.x    = 0.0f;
    this->maxSpeed.x = 0.0f;
}

void Splounder::executeState_Turn() {
    
    
    if (this->physicsMgr.isOnGround()) this->speed.y = 0.0f;

    u32 step = this->chasing ? fixDeg(6.0f) : fixDeg(3.0f);
    if (moveValueWithOverflowTo(this->rotation.y, Direction::directionToRotationList[this->direction], step, this->direction)) {
        this->doStateChange(&Splounder::StateID_Walk);
    }
}

void Splounder::endState_Turn() {
    this->rotation.y = Direction::directionToRotationList[this->direction];
}

/** STATE: Launch */

void Splounder::beginState_Launch() {
    this->direction = this->directionToPlayerH(this->position);
    this->rotation.y = Direction::directionToRotationList[this->direction];

    this->model->playSklAnim("throw", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->speed.x = 0.0f;
    this->target->speed.y = 1.0f + this->launchHeight / 14.0f;
}

void Splounder::executeState_Launch() {
    
   
    if (this->physicsMgr.isOnGround()) {
        this->speed.y = 0.0f;
    }

    if (this->model->sklAnims[0]->frameCtrl.isDone()) {
        this->doStateChange(&Splounder::StateID_Walk);
    }
}

void Splounder::endState_Launch() {
    this->model->playSklAnim("walk", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
}

void Splounder::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type != StageActor::Type::Player && hcOther->owner->type != StageActor::Type::Yoshi){
        return;
    }

    Splounder* self = static_cast<Splounder*>(hcSelf->owner);

    self->target = hcOther->owner;
    self->targetInitialY = self->target->position.y;
    self->doStateChange(&Splounder::StateID_Launch);
}
