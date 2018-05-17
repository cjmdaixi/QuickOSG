import QtQuick 2.6
import QtQml.StateMachine 1.0 as SM
import QtQuick.Window 2.2

SM.StateMachine{
    id: root
    initialState: initState

    SM.State{
        id: initState
        onEntered:{
			console.log("Enter init state...");
		}
		onExited:{
			console.log("Exit init state...");
		}
	}
}
