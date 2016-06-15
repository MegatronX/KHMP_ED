/*enum PlayerInput
{
    P1Input = 0,
    P2Input = 1,
    P3Input = 2,
    P4Input = 3,
    Invalid
};
#define InputCount 12
#define MaxPlayerCount 2
	enum InputAction
{
    Confirm,
    Cancel,
    Aux1,
    Aux2,
    Start,
    Select,
    Up,
    Down,
    Left,
    Right,
    AuxLeft,
    AuxRight,
    MouseLeft,
    MouseRight,
    MouseMove,
    InvalidAction
};*/
var PlayerInput = Object.freeze(
{
    P1Input: 0,
    P2Input: 1,
    P3Input: 2,
    P4Input: 3,
    Invalid: 4
    });
var InputAction = Object.freeze(
    {Confirm: 0,
    Cancel: 1,
    Aux1: 2,
    Aux2: 3,
    Start: 4,
    Select: 5,
    Up: 6,
    Down: 7,
    Left: 8,
    Right: 9,
    AuxLeft: 10,
    AuxRight: 11,
    MouseLeft: 12,
    MouseRight: 13,
    MouseMove: 14,
    InvalidAction: 15
    }
    );