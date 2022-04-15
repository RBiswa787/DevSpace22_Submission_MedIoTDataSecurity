import logo from './logo.svg';
import './App.css';

function App() {
  var pid="A687K6"
  var name="Jacob Zelensky"
  var phno="+91 973388192"
  var height="187"
  var BP="160"
  var BPM="71"
  BP=BP+" mmHg"
  BPM=BPM+" bpm"
  height=height+" cm"
  return (
    <div className="App">
      <section className="info">
        <div className="pid">Patient Id : {pid} </div>
        <div className="details">
          <h2 className="name">Name : {name}</h2>
          <h2 className="phno">Phone : {phno}</h2>
          <h2 className="Height" id="r">Height : {height}</h2>
          <h2 className="BPH" id="r">Blood Pressure : {BP}</h2>
          <h2 className="BPM" id="r">Beats Per Minute : {BPM}</h2>
          <div className="response">
        <form>
          <label for="fname">Diagnosis:</label>
          <input type="text" id="fname" name="fname"></input><br></br>
          <label for="lname">Prescription:</label>
          <input type="text" id="lname" name="lname"></input>
        </form>
        </div>
        </div>
        
      </section>
    </div>
  );
}

export default App;
