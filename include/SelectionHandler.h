// SelectionTool.h
#pragma once
#include <unordered_set>
#include <functional>
#include <raylib.h>
#include "LogicElements.h"
#include "Component.h"

struct Bounds { float x,y,w,h; };
enum class SelMode { Replace, Add, Toggle };

class SelectionTool : public IInputHandler {
public:
    SelectionTool(SP_Circuit circuit)
        : circuit(circuit) {}

    void OnInputEvent(InputEvent& e) {
        if (e.type != InputType::Mouse)
        {
            return;
        }
        if (!dragging && e.mouseState == MouseEventState::Down && !e.consumed
        && InputResolver::getDragMode() == DragMode::Normal  ) 
        {
            //InputResolver::setSelectedHandler(std::vector<IInputHandler*>{});
            // boş alan tespiti
            if (!hitAnyComponent(e.pos)) 
            {
                dragging = true;
                startScreen = toVec2(e.pos);
                curScreen   = startScreen;
                mode = decideMode(e);
                e.consumed = true; // capture
                InputResolver::setDragMode(DragMode::MarqueeSelecting);
            }
        }
        else if (dragging && e.mouseState == MouseEventState::Down && 
        InputResolver::getDragMode() == DragMode::MarqueeSelecting ) 
        {
            curScreen = toVec2(e.pos);
            std::vector<std::weak_ptr<IInputHandler>> components = getHitComponents(startScreen , curScreen);
            InputResolver::setSelectedHandler(components);
            e.consumed = true;
            InputResolver::setDragMode(DragMode::MarqueeSelecting);
        }
        else if (dragging && e.mouseState == MouseEventState::Release) 
        {
            curScreen = toVec2(e.pos);
            dragging = false;
            e.consumed = true;
            InputResolver::setDragMode(DragMode::Normal);
        }
    }

    // Move event yoksa her frame çağır:
    void UpdatePerFrame() {
        if (dragging && !hasMoveEvents) curScreen = GetMousePosition();
    }

    void DrawOverlay() const {
        if (!dragging) return;
        Rectangle r = rectFromPts(startScreen, curScreen);
        DrawRectangle((int)r.x,(int)r.y,(int)r.width,(int)r.height, Color{100,150,255,60});
        DrawRectangleLinesEx(r, 1.5f, Color{100,150,255,200});
    }

private:
    bool dragging=false;
    bool hasMoveEvents=true; // sende Move push’lamıyorsan false yap
    Vector2 startScreen{}, curScreen{};
    SelMode mode = SelMode::Replace;
    SP_Circuit circuit; 
    std::function<size_t()> compCount;
    std::function<Bounds(size_t)> getBounds;
    std::function<void(const std::unordered_set<size_t>&, SelMode)> applySelection;

    static Vector2 toVec2(const Vector2& p){ return {(float)p.x,(float)p.y}; }

    Rectangle rectFromPts(Vector2 a, Vector2 b) const 
    {
        Rectangle r;
        r.x=std::min(a.x,b.x); r.y=std::min(a.y,b.y);
        r.width = std::abs(a.x-b.x); r.height=std::abs(a.y-b.y);
        return r;
    }
    SelMode decideMode(const InputEvent& e) const 
    {
        if (e.shift) return SelMode::Add;
        if (e.ctrl)  return SelMode::Toggle;
        return SelMode::Replace;
    }
    bool hitAnyComponent(const Vector2& screenPos) const 
    {
        for (size_t i=0;i < circuit->gates.size(); i++){
            auto b = circuit->gates[i]->bd;
            if (screenPos.x>=b.x && screenPos.x<=b.x+b.width 
            && screenPos.y>=b.y && screenPos.y<=b.y+b.height) return true;
        }
        return false; 
    }
    std::vector<std::weak_ptr<IInputHandler>> getHitComponents(const Vector2& startPos , const Vector2& curPos)
    {
        std::vector<std::weak_ptr<IInputHandler>> indices; 
        //Rectangle cur = { startPos.x , startPos.y , curPos.x - startPos.x , curPos.y - startPos.y};
        Rectangle cur = { std::min(startPos.x,curPos.x) ,std::min( startPos.y , curPos.y), std::abs(curPos.x - startPos.x)
        , std::abs(curPos.y - startPos.y)};
        for (size_t i=0;i < circuit->gates.size(); i++){
            auto b = circuit->gates[i]->bd;
            if (intersects(cur , b))
            {
                indices.push_back(circuit->gates[i]);
            }
        }   
        return indices;
    }
    static bool intersects(const Rectangle& A, const Rectangle& B)
    {
        return !(A.x > B.x+B.width || A.x+A.width < B.x ||
                 A.y > B.y+B.height|| A.y+A.height< B.y);
    }
    void commit() 
    {
        // Rectangle wr = worldRect();
        // // tıklama sayma eşiği (tek tık gibi davranmak için)
        // if (wr.width*wr.height < 4.0f) return;

        // std::unordered_set<size_t> picked;
        // for (size_t i=0;i<compCount();++i){
        //     auto b = getBounds(i);
        //     Rectangle aabb{b.x,b.y,b.w,b.h};
        //     if (intersects(aabb, wr)) picked.insert(i);
        // }
        // applySelection(picked, mode); // dışarıda seçimi güncelle (ve undo kaydet)
    }
};
