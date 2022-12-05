import axios from "axios";

export default axios.create({
  baseURL: "https://sauravniraula.pythonanywhere.com/"
  // baseURL: "http://localhost:8000/"
})