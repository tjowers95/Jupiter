import React, {Component} from 'react';
import ReactDOM from 'react-dom';

class JupiterClient extends Component {
    constructor() {
        super();
        this.state = {};
    }

    render() {
        return <h1>Jupiter</h1>;
    }
}

ReactDOM.render(<JupiterClient/>, document.getElementById('root'));
