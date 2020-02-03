import React from 'react';
import './App.css';

global.ss = "ss"

//Input
class TextInput extends React.Component {
  OnTextChange = event => {
    this.props.onChange(event.target.value);
  }
  render() {
    return (
      <div>
        <label className="TxtLabel">Напиши что-нибудь </label>
        <input className="TxtInput" 
                type="text" 
                name="myText" 
                onChange={this.OnTextChange}/>
      </div>
    );
  }
}


//Button
class Button extends React.Component {
  OnBtnClick = (event) => {
    this.props.onClick("f");
  }

  render() {
    return (
      <div>
        <button className="TxtButton"
        onClick={this.OnBtnClick}
        >Нажми меня</button>
      </div>
    );
  }
}

class Parent extends React.Component{
  state = {
    Text: "",
    DText: ""
  }
  constructor(props) {
    super(props)
    this.handler = this.handler.bind(this);
    this.ClickEvent = this.ClickEvent.bind(this);
  }
  ClickEvent(a) {
    this.setState({
      DText: this.state.Text
    })
  }

  handler(text){
    this.setState({
      Text: text
  });
  }
  render() {
    return (
      <div>
        <TextInput onChange={this.handler}></TextInput>
        <Button onClick={this.ClickEvent}></Button>
        <label className="TxtLabel">{this.state.DText}</label>
      </div>
    );
  }
}

function App() {
  return (
    <div className="App">
      <header className="App-header">
      <Parent />
      </header>
    </div>
  );
}

export default App;
