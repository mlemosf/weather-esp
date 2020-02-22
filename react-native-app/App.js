import React, { Component } from "react";
import { FlatList, ActivityIndicator, RefreshControl, StyleSheet, Text, TouchableOpacity, View } from "react-native";
import Card from "./shared/card";
import Header from "./shared/header"

// Globals
const API_ENDPOINT="http://192.168.0.26";

export default class WeatherInfo  extends Component {
	constructor(props) {
		super(props);
		this.state= {
			loading: true,
			dataSource: []
		};
	}

	getData = () => {
		fetch(API_ENDPOINT)
		.then(response => response.json())
		.then((responseJson) => {
			this.setState({
				loading: false,
				dataSource: responseJson
			})
		})
		.catch(error => console.log(error)); // to catch errors if any
	}

	componentDidMount(){
		this.getData();		
	};

	onRefresh() {
		this.setState({ dataSource: [] });
		this.getData();
	}

	FlatListItemSeparator = () => {
	return (
  		<View style={{
    		height: .8,
     		width:"100%",
     		backgroundColor: "#fff",
		}}/>
	);}
	

	renderItem=(data)=>
		<TouchableOpacity style={styles.container}>
			<Card props={data.item}> 
			</Card>
		</TouchableOpacity>
	
	render() {
		const title="WeatherESP";
		if (this.state.loading){
			return(
				<View style={styles.loader}>
					<ActivityIndicator size="large" color="#0c9"/>
				</View>
			)
		}
    return(
      <View style={styles.container}>	
		<Header title={title}/>
		<FlatList
          data={this.state.dataSource}
		  ItemSeparatorComponent={this.FlatListItemSeparator}
          renderItem={item=>this.renderItem(item)}
		  keyExtractor={item=>item.key.toString()}
          refreshControl={
			<RefreshControl
		  		refreshing={this.state.loading}
		  		onRefresh={this.onRefresh.bind(this)}
			/>
		  }
		/>
      </View>

	);
  }
}

const styles = StyleSheet.create({
  container: {
	flex: 1,
	backgroundColor: "#fff",
	paddingTop: 10,
  },
  item: {
    fontSize: 30,
    height: 50,
	color: "#fff"
  }
})
