package cs

import (
	"fmt"

	"github.com/mjpancake/ih/ako"
)

var decoder = ako.NewDecoder([]interface{}{
	LookAround{},
	Heartbeat{},
	RoomCreate{},
	RoomJoin{},
	RoomQuit{},
	Seat{},
	Action{},
	GetReplayList{},
	GetReplay{},
})

func FromJson(breq []byte) (interface{}, error) {
	cs, err := decoder.FromJson(breq)
	if err != nil {
		return nil, fmt.Errorf("cs.FromJson: %v", err)
	}

	switch cs := cs.(type) {
	case *RoomCreate:
		if !cs.AiNum.Valid() ||
			cs.AiNum.NeedUser()+len(cs.AiGids) > 4 ||
			len(cs.AiGids) != cs.AiNum.NeedAi() {
			err = fmt.Errorf("invalid %T %v", cs, cs)
		}
	default:
		// no arg to validate
	}

	return cs, err
}

func ToJson(cs interface{}) []byte {
	return ako.ToJson(cs)
}
