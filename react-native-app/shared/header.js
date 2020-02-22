import React from 'react';
import {Alert, TouchableOpacity, StyleSheet, Text, View } from 'react-native';
import { MaterialIcons } from '@expo/vector-icons'

const Header = ({title}) => {
	return(
		<View style={styles.header}>
			<Text style={styles.headerText}>{title}</Text>
		</View>
	);
}

const styles = StyleSheet.create({
	header: {
		width: "100%",
		height: "10%",
		alignItems: "center",
		backgroundColor: "#333"
	},
	headerText: {
		fontWeight: "bold",
		fontSize: 30,
		color: "#fff",
		textAlign: "center",
		paddingTop: 20
	}
	
});

export default Header;
